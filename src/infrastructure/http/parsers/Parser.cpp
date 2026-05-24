/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:40:42 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/24 23:12:44 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/parsers/Parser.hpp"
#include "http/message/IRequest.hpp"
#include "infrastructure/http/Methods.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"
#include <algorithm>

namespace
{
	bool is_valid_target_syntax(
		std::vector<char>::const_iterator it_start, std::vector<char>::const_iterator it_end
	)
	{
		if (it_start == it_end)
			return (false);
		if (*it_start != '/')
			return (false);
		if (std::find_if(it_start, it_end, is_invalid_target_char) != it_end)
			return (false);
		return (true);
	}

	bool is_valid_key_syntax(
		std::vector<char>::const_iterator it_start, std::vector<char>::const_iterator it_end
	)
	{
		if (it_start == it_end)
			return (false);
		if (std::find_if(it_start, it_end, is_invalid_key_char) != it_end)
			return (false);
		return (true);
	}

	bool is_valid_value_syntax(
		std::vector<char>::const_iterator it_start, std::vector<char>::const_iterator it_end
	)
	{
		if (it_start == it_end)
			return (false);
		if (std::find_if(it_start, it_end, is_invalid_value_char) != it_end)
			return (false);
		return (true);
	}

	bool is_invalid_target_char(unsigned char c) { return (!(std::isprint(c) || c >= 128)); }

	bool is_invalid_key_char(unsigned char c)
	{
		static const std::string specials_authorized = "!#$%&'*+-.^_`|~";

		return (!(std::isalnum(c) || specials_authorized.find(c) != std::string::npos));
	}

	bool is_invalid_value_char(unsigned char c)
	{
		return (!(std::isprint(c) || c == '\t' || c >= 128));
	}

	bool is_not_whitespaces(char c) { return (c != ' ' && c != '\t'); }

	char to_lower_safe(unsigned char c) { return (static_cast<char>(std::tolower(c))); }

	void trim(std::string &str, char const *to_trim)
	{
		std::size_t end = str.find_last_not_of(to_trim);
		if (end != std::string::npos)
			str.erase(end + 1);
		else
		{
			str.clear();
			return;
		}

		std::size_t start = str.find_first_not_of(to_trim);
		if (start != std::string::npos && start != 0)
			str.erase(0, start);
	}
} // namespace

namespace http
{
	char const		  _crlf[] = "\r\n";
	std::size_t const _crlfSize = 2;
	char const		  _whiteSpaces[] = "\t ";
	std::size_t const _whiteSpaceSize = 2;

	ParsingState::Step Parser::parse(std::vector<char> const &readBuf, ParsingState &state)
	{
		std::vector<char>::const_iterator it_start = readBuf.begin() + state.pos;

		if (state.step == ParsingState::start)
			skipLeadingCrlf(it_start, readBuf, state);

		std::vector<char>::const_iterator it_line_end =
			std::search(it_start, readBuf.end(), _crlf, _crlf + _crlfSize);

		if (it_line_end != readBuf.end())
		{
			switch (state.step)
			{
			case ParsingState::requestLine:
				parseRequestLine(it_start, it_line_end, state);
				break;
			case ParsingState::header:
				parseHeaderLine(it_start, it_line_end, state);
				break;
			default:
				break;
			}
			// if (context.step == ParsingContext::Complete)
			// {
			// 	RequestEntity	request_entity = RequestMapper::toDomain(this->_requestDto);
			// 	this->_requestInputPort->handle(request_entity);
			// }
			state.pos += std::distance(it_start, it_line_end) + _crlfSize;
		}
		return (state.step);
	}

	void Parser::parseRequestLine(
		std::vector<char>::const_iterator itStart,
		std::vector<char>::const_iterator itLineEnd,
		ParsingState					 &state
	)
	{
		if (hasLineBreak(itStart, itLineEnd))
			throw Exception(Exception::invalidLineBreak);

		std::vector<char>::const_iterator it = itStart;

		state.request.method = extractMethod(it, itLineEnd);
		state.request.target = extractTarget(it, itLineEnd);
		state.request.protocol = extractProtocol(it, itLineEnd);

		if (std::find_if(it, itLineEnd, is_not_whitespaces) != itLineEnd)
			throw Exception(Exception::malformedRequestLine);

		state.step = ParsingState::header;
	}

	void Parser::parseHeaderLine(
		std::vector<char>::const_iterator itStart,
		std::vector<char>::const_iterator itLineEnd,
		ParsingState					 &state
	)
	{
		if (itStart == itLineEnd)
		{
			state.step = ParsingState::body;
			return;
		}

		if (hasLineBreak(itStart, itLineEnd))
			throw Exception(Exception::invalidLineBreak);

		std::vector<char>::const_iterator it_colon;
		it_colon = std::find(itStart, itLineEnd, ':');
		if (it_colon == itLineEnd)
			throw Exception(Exception::malformedHeaderLine);

		if (!is_valid_key_syntax(itStart, it_colon))
			throw Exception(Exception::invalidHeaderKey);
		std::string key(itStart, it_colon);
		std::transform(key.begin(), key.end(), key.begin(), to_lower_safe);

		if (!is_valid_value_syntax(it_colon + 1, itLineEnd))
			throw Exception(Exception::invalidHeaderValue);
		std::string value(it_colon + 1, itLineEnd);
		trim(value, _whiteSpaces);

		state.request.headers[key] = value;
	}

	std::string Parser::extractMethod(
		std::vector<char>::const_iterator &it, std::vector<char>::const_iterator itLineEnd
	)
	{
		std::vector<char>::const_iterator it_method_end =
			std::find_first_of(it, itLineEnd, _whiteSpaces, _whiteSpaces + _whiteSpaceSize);
		if (it_method_end == itLineEnd)
			throw Exception(Exception::malformedRequestLine);

		std::string method(it, it_method_end);
		if (!isMethodSupported(method))
			throw Exception(Exception::invalidMethod);

		it = it_method_end;
		return (method);
	}

	std::string Parser::extractTarget(
		std::vector<char>::const_iterator &it, std::vector<char>::const_iterator itLineEnd
	)
	{
		std::vector<char>::const_iterator it_target_start =
			std::find_if(it, itLineEnd, is_not_whitespaces);
		if (it_target_start == itLineEnd)
			throw Exception(Exception::malformedRequestLine);

		std::vector<char>::const_iterator it_target_end = std::find_first_of(
			it_target_start, itLineEnd, _whiteSpaces, _whiteSpaces + _whiteSpaceSize
		);
		if (it_target_end == itLineEnd)
			throw Exception(Exception::malformedRequestLine);

		if (!is_valid_target_syntax(it_target_start, it_target_end))
			throw Exception(Exception::invalidTarget);
		std::string target(it_target_start, it_target_end);

		it = it_target_end;
		return (target);
	}

	std::string Parser::extractProtocol(
		std::vector<char>::const_iterator &it, std::vector<char>::const_iterator itLineEnd
	)
	{
		std::vector<char>::const_iterator it_protocol_start =
			std::find_if(it, itLineEnd, is_not_whitespaces);
		if (it_protocol_start == itLineEnd)
			throw Exception(Exception::malformedRequestLine);

		std::vector<char>::const_iterator it_protocol_end = std::find_first_of(
			it_protocol_start, itLineEnd, _whiteSpaces, _whiteSpaces + _whiteSpaceSize
		);

		std::string protocol(it_protocol_start, it_protocol_end);

		it = it_protocol_end;
		return (protocol);
	}

	bool Parser::hasLineBreak(
		std::vector<char>::const_iterator itStart, std::vector<char>::const_iterator itEnd
	)
	{
		return ((std::find_first_of(itStart, itEnd, _crlf, _crlf + _crlfSize) != itEnd));
	}

	void Parser::skipLeadingCrlf(
		std::vector<char>::const_iterator &itStart,
		std::vector<char> const			  &readBuf,
		ParsingState					  &state
	)
	{
		while (std::search(itStart, readBuf.end(), _crlf, _crlf + _crlfSize) == itStart)
		{
			itStart += _crlfSize;
			state.pos += _crlfSize;
		}
		if (itStart != readBuf.end() || (*itStart == '\r' && itStart + 1 != readBuf.end()))
			state.step = ParsingState::requestLine;
	}
} // namespace http
