/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:40:42 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:14:08 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/parsers/Parser.hpp"
#include "infrastructure/http/Methods.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"
#include "infrastructure/http/parsers/IRequestValidationPolicy.hpp"
#include <algorithm>
#include <cerrno>

namespace {
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
	static std::string const specials_authorized = "?!#$%&'*+-.^_`|~";

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

namespace http {
char const Parser::_crlf[] = "\r\n";
char const Parser::_whiteSpaces[] = "\t ";

Parser::Parser(IRequestValidationPolicy &requestValidationPolicy)
	: _requestValidationPolicy(requestValidationPolicy)
{}

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
					readBuf.erase(it_start, it_start + sizeof(_crlf) - 1);
					break;
				}
				if (*it_start == '\r' && it_start + 1 != readBuf.end())
					state.step = ParsingState::requestLine;
			case ParsingState::requestLine:
				std::vector<char>::iterator it_start = readBuf.begin();
				std::vector<char>::iterator it_line_end = findCRLF(readBuf);

				state.currenLineSize += std::distance(it_start, it_line_end);
				validateRequestLineSize(state.currenLineSize);
				if (it_line_end == readBuf.end())
				{
					can_continue = false;
					break;
				}
				parseRequestLine(it_start, it_line_end, state);
				readBuf.erase(it_start, it_line_end + sizeof(_crlf) - 1);
				state.currenLineSize = 0;
				state.step = ParsingState::header;
				break;
			case ParsingState::header:
				std::vector<char>::iterator it_start = readBuf.begin();
				std::vector<char>::iterator it_line_end = findCRLF(readBuf);

				state.currenLineSize += std::distance(it_start, it_line_end);
				validateHeaderLineSize(state.currenLineSize);
				if (it_line_end == readBuf.end())
				{
					can_continue = false;
					break;
				}
				++state.currentHeaderCount;
				validateHeaderCount(state.currentHeaderCount);
				if (it_start == it_line_end)
				{
					if (state.request.contentLength != 0 && expectsBody(state.request.method))
					{
						readBuf.erase(it_start, it_start + sizeof(_crlf) - 1);
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
				readBuf.erase(it_start, it_line_end + sizeof(_crlf) - 1);
				state.currenLineSize = 0;
				break;
			case ParsingState::body:
				parseBody(readBuf, state);
				readBuf.clear();
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
	extractTargetandQuery(it, itLineEnd, state);
	state.request.protocol = extractProtocol(it, itLineEnd);

	if (std::find_if(it, itLineEnd, is_not_whitespaces) != itLineEnd)
		throw Exception(Exception::requestLineMalformed);
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
		throw Exception(Exception::headerLineMalformed);

	if (!is_valid_key_syntax(itStart, it_colon))
		throw Exception(Exception::headerKeyInvalid);
	std::string key(itStart, it_colon);
	std::transform(key.begin(), key.end(), key.begin(), to_lower_safe);

	if (!is_valid_value_syntax(it_colon + 1, itLineEnd))
		throw Exception(Exception::headerValueInvalid);
	std::string value(it_colon + 1, itLineEnd);
	trim(value, _whiteSpaces);

	state.request.headers[key] = value;
}

void Parser::parseContentLength(ParsingState &state)
{
	std::map<std::string, std::string>::const_iterator it =
		state.request.headers.find("content-length");

	if (it == state.request.headers.end())
	{
		if (expectsBody(state.request.method))
			throw Exception(Exception::contentLengthRequired);
		return;
	}

	std::string content_length = (*it).second;
	if (content_length.empty())
		throw Exception(Exception::contentLengthInvalid);

	char *endptr;
	errno = 0;
	unsigned long val = std::strtoul(content_length.c_str(), &endptr, 10);

	if (errno == ERANGE || *endptr != '\0' || content_length[0] == '-')
		throw Exception(Exception::contentLengthInvalid);
	if (val > _requestValidationPolicy.getMaxBodySize(state.request.target))
		throw Exception(Exception::bodyTooLarge);
	state.request.contentLength = static_cast<size_t>(val);
}

void Parser::parseBody(std::vector<char> const &readBuf, ParsingState &state)
{
	state.bodyBytesRead += readBuf.size();
	if (state.bodyBytesRead > _requestValidationPolicy.getMaxBodySize(state.request.target))
		throw Exception(Exception::bodyTooLarge);
	state.request.body.append(readBuf);
}

std::string Parser::extractMethod(
	std::vector<char>::const_iterator &it, std::vector<char>::const_iterator itLineEnd
)
{
	std::vector<char>::const_iterator it_method_end =
		std::find_first_of(it, itLineEnd, _whiteSpaces, _whiteSpaces + sizeof(_whiteSpaces) - 1);
	if (it_method_end == itLineEnd)
		throw Exception(Exception::requestLineMalformed);

	std::string method(it, it_method_end);
	if (!isMethodSupported(method))
		throw Exception(Exception::methodInvalid);

	it = it_method_end;
	return (method);
}

void Parser::extractTargetandQuery(
	std::vector<char>::const_iterator &it,
	std::vector<char>::const_iterator  itLineEnd,
	ParsingState					  &state
)
{
	std::vector<char>::const_iterator it_target_start =
		std::find_if(it, itLineEnd, is_not_whitespaces);
	if (it_target_start == itLineEnd)
		throw Exception(Exception::requestLineMalformed);

	std::vector<char>::const_iterator it_target_end = std::find_first_of(
		it_target_start, itLineEnd, _whiteSpaces, _whiteSpaces + sizeof(_whiteSpaces) - 1
	);
	if (it_target_end == itLineEnd)
		throw Exception(Exception::requestLineMalformed);

	if (!is_valid_target_syntax(it_target_start, it_target_end))
		throw Exception(Exception::targetInvalid);

	std::vector<char>::const_iterator it_query = std::find(it_target_start, it_target_end, '?');

	state.request.target = std::string(it_target_start, it_query);
	state.request.query = std::string(it_query + 1, it_target_end);

	it = it_target_end;
}

std::string Parser::extractProtocol(
	std::vector<char>::const_iterator &it, std::vector<char>::const_iterator itLineEnd
)
{
	std::vector<char>::const_iterator it_protocol_start =
		std::find_if(it, itLineEnd, is_not_whitespaces);
	if (it_protocol_start == itLineEnd)
		throw Exception(Exception::requestLineMalformed);

	std::vector<char>::const_iterator it_protocol_end = std::find_first_of(
		it_protocol_start, itLineEnd, _whiteSpaces, _whiteSpaces + sizeof(_whiteSpaces) - 1
	);

	std::string protocol(it_protocol_start, it_protocol_end);

	if (protocol != _requestValidationPolicy.getSupportedHttpVersion())
		throw Exception(Exception::versionInvalid);
	it = it_protocol_end;
	return (protocol);
}

bool Parser::hasLineBreak(
	std::vector<char>::const_iterator itStart, std::vector<char>::const_iterator itEnd
)
{
	return ((std::find_first_of(itStart, itEnd, _crlf, _crlf + sizeof(_crlf) - 1) != itEnd));
}

std::vector<char>::iterator Parser::findCRLF(std::vector<char> &readBuf)
{
	return (std::search(readBuf.begin(), readBuf.end(), _crlf, _crlf + sizeof(_crlf) - 1));
}

void Parser::validateRequestLineSize(std::size_t size)
{
	if (size > _requestValidationPolicy.getMaxRequestLineSize())
		throw Exception(Exception::requestLineTooLarge);
}

void Parser::validateHeaderLineSize(std::size_t size)
{
	if (size > _requestValidationPolicy.getMaxHeaderLineSize())
		throw Exception(Exception::requestLineTooLarge);
}

void Parser::validateHeaderCount(std::size_t count)
{
	if (count > _requestValidationPolicy.getMaxHeaderCount())
		throw Exception(Exception::HeaderCountTooLarge);
}
} // namespace http
