/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:40:42 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/26 19:19:47 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/parsers/Parser.hpp"
#include "http/message/IRequest.hpp"
#include "infrastructure/http/Methods.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"
#include <algorithm>
#include <cerrno>

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

	ParsingState::Step Parser::parse(std::vector<char> &readBuf, ParsingState &state)
	{
		bool can_continue = true;

		while (can_continue && !readBuf.empty())
		{
			switch (state.step)
			{
				case ParsingState::start:
					std::vector<char>::iterator it_start = readBuf.begin();
					std::vector<char>::iterator it_line_end = findCRLF(readBuf);
					if (it_start == it_line_end)
					{
						readBuf.erase(it_start, it_start + _crlfSize);
						break;
					}
					if (*it_start == '\r' && it_start + 1 != readBuf.end())
						state.step = ParsingState::requestLine;
				case ParsingState::requestLine:
					std::vector<char>::iterator it_start = readBuf.begin();
					std::vector<char>::iterator it_line_end = findCRLF(readBuf);

					if (it_line_end == readBuf.end())
					{
						can_continue = false;
						break;
					}
					parseRequestLine(it_start, it_line_end, state);
					readBuf.erase(it_start, it_line_end + _crlfSize);
					state.step = ParsingState::header;
					break;
				case ParsingState::header:
					std::vector<char>::const_iterator it_start = readBuf.begin();
					std::vector<char>::const_iterator it_line_end = findCRLF(readBuf);

					if (it_line_end == readBuf.end())
					{
						can_continue = false;
						break;
					}
					if (it_start == it_line_end)
					{
						if (state.request.contentLength != 0 && expectsBody(state.request.method))
						{
							readBuf.erase(it_start, it_start + _crlfSize);
							state.step = ParsingState::body;
							break;
						}
						else
						{
							state.step = ParsingState::complete;
							can_continue = false;
							break;
						}
					}
					parseRequestLine(it_start, it_line_end, state);
					parseContentLength(state);
					readBuf.erase(it_start, it_line_end + _crlfSize);
					break;
				case ParsingState::body:
					parseBody(it_start, it_line_end, state);
					if (state.bodyBytesRead == state.request.contentLength)
					{
						state.step = ParsingState::complete;
						can_continue = false;
						break;
					}
				default:
					break;
			}
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
	}

	void Parser::parseHeaderLine(
		std::vector<char>::const_iterator itStart,
		std::vector<char>::const_iterator itLineEnd,
		ParsingState					 &state
	)
	{
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

	void Parser::parseContentLength(ParsingState &state)
	{
		std::map<std::string, std::string>::const_iterator it =
			state.request.headers.find("content-length");

		if (it == state.request.headers.end())
			return;

		std::string content_length = state.request.headers["content-length"];
		if (content_length.empty())
			throw Exception(Exception::invalidContentLength);

		char *endptr;
		errno = 0;
		unsigned long val = std::strtoul(content_length.c_str(), &endptr, 10);

		if (errno == ERANGE || *endptr != '\0' || content_length[0] == '-')
			throw Exception(Exception::invalidContentLength);
		// if (val > setting.maxbody)
		// 	throw
		state.request.contentLength = static_cast<size_t>(val);
	}

	void Parser::parseBody(
		std::vector<char>::const_iterator itStart,
		std::vector<char>::const_iterator itLineEnd,
		ParsingState					 &state
	)
	{
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

	std::vector<char>::iterator Parser::findCRLF(std::vector<char> &readBuf)
	{
		return (std::search(readBuf.begin(), readBuf.end(), _crlf, _crlf + _crlfSize));
	}
} // namespace http
