/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:40:42 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/27 08:20:05 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/request/Parser.hpp"
#include "infrastructure/http/Constants.hpp"
#include "infrastructure/http/IHttpVersionProvider.hpp"
#include "infrastructure/http/Methods.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"
#include "infrastructure/http/request/IRequestValidationPolicy.hpp"
#include <algorithm>
#include <cerrno>

namespace {
bool is_invalid_target_char(unsigned char c);
bool is_invalid_key_char(unsigned char c);
bool is_invalid_value_char(unsigned char c);

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
	return (!(std::isprint(c) || c == http::HT || c >= 128));
}

bool is_not_white_spaces(char c) { return (c != http::SP && c != http::HT); }

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
namespace request {

std::size_t const Parser::DEFAULT_MAX_REQUEST_LINE_SIZE;
std::size_t const Parser::DEFAULT_MAX_HEADER_LINE_SIZE;
std::size_t const Parser::DEFAULT_MAX_HEADER_COUNT;
std::size_t const Parser::DEFAULT_MAX_BODY_SIZE;

Parser::Parser(
	IRequestValidationPolicy &requestValidationPolicy, IHttpVersionProvider &httpVersionProvider
)
	: _requestValidationPolicy(requestValidationPolicy), _httpVersionProvider(httpVersionProvider)
{
	_maxRequestLineSize =
		std::min(_requestValidationPolicy.getMaxRequestLineSize(), DEFAULT_MAX_REQUEST_LINE_SIZE);

	_maxHeaderLineSize =
		std::min(_requestValidationPolicy.getMaxHeaderLineSize(), DEFAULT_MAX_HEADER_LINE_SIZE);
	_maxHeaderCount =
		std::min(_requestValidationPolicy.getMaxHeaderCount(), DEFAULT_MAX_HEADER_COUNT);
	_maxBodySize = std::min(_requestValidationPolicy.getMaxBodySize(), DEFAULT_MAX_BODY_SIZE);
}
Parser::Step Parser::parse(std::vector<char> &inputBuf, State &state)
{
	bool can_continue = true;

	while (can_continue && !inputBuf.empty())
	{
		switch (state.step)
		{
			case Parser::start:
			{
				std::vector<char>::iterator it_start = inputBuf.begin();
				std::vector<char>::iterator it_line_end = findCRLF(inputBuf);
				if (it_start == it_line_end)
				{
					inputBuf.erase(it_start, it_start + sizeof(CRLF) - 1);
					break;
				}
				if (*it_start == CR && it_start + 1 == inputBuf.end())
				{
					can_continue = false;
					break;
				}
				state.step = Parser::requestLine;
				break;
			}
			case Parser::requestLine:
			{
				std::vector<char>::iterator it_start = inputBuf.begin();
				std::vector<char>::iterator it_line_end = findCRLF(inputBuf);

				state.currenLineSize += std::distance(it_start, it_line_end);
				validateRequestLineSize(state.currenLineSize);
				if (it_line_end == inputBuf.end())
				{
					can_continue = false;
					break;
				}
				parseRequestLine(it_start, it_line_end, state);
				inputBuf.erase(it_start, it_line_end + sizeof(CRLF) - 1);
				state.currenLineSize = 0;
				state.step = Parser::header;
				break;
			}
			case Parser::header:
			{
				std::vector<char>::iterator it_start = inputBuf.begin();
				std::vector<char>::iterator it_line_end = findCRLF(inputBuf);

				state.currenLineSize += std::distance(it_start, it_line_end);
				validateHeaderLineSize(state.currenLineSize);
				if (it_line_end == inputBuf.end())
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
						inputBuf.erase(it_start, it_start + sizeof(CRLF) - 1);
						state.step = Parser::body;
						break;
					}
					else
					{
						state.step = Parser::complete;
						can_continue = false;
						break;
					}
				}
				parseHeaderLine(it_start, it_line_end, state);
				parseContentLength(state);
				inputBuf.erase(it_start, it_line_end + sizeof(CRLF) - 1);
				state.currenLineSize = 0;
				break;
			}
			case Parser::body:
			{
				parseBody(inputBuf, state);
				inputBuf.clear();
				if (state.bodyBytesRead == state.request.contentLength)
				{
					state.step = Parser::complete;
					can_continue = false;
					break;
				}
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
	State							 &state
)
{
	if (hasLineBreak(itStart, itLineEnd))
		throw Exception(Exception::invalidLineBreak);

	std::vector<char>::const_iterator it = itStart;

	state.request.method = extractMethod(it, itLineEnd);
	extractTargetandQuery(it, itLineEnd, state);
	state.request.protocol = extractProtocol(it, itLineEnd);

	if (std::find_if(it, itLineEnd, is_not_white_spaces) != itLineEnd)
		throw Exception(Exception::requestLineMalformed);
}

void Parser::parseHeaderLine(
	std::vector<char>::const_iterator itStart,
	std::vector<char>::const_iterator itLineEnd,
	State							 &state
)
{
	if (hasLineBreak(itStart, itLineEnd))
		throw Exception(Exception::invalidLineBreak);

	std::vector<char>::const_iterator it_colon;
	it_colon = std::find(itStart, itLineEnd, COLON);
	if (it_colon == itLineEnd)
		throw Exception(Exception::headerLineMalformed);

	if (!is_valid_key_syntax(itStart, it_colon))
		throw Exception(Exception::headerKeyInvalid);
	std::string key(itStart, it_colon);
	std::transform(key.begin(), key.end(), key.begin(), to_lower_safe);

	if (!is_valid_value_syntax(it_colon + 1, itLineEnd))
		throw Exception(Exception::headerValueInvalid);
	std::string value(it_colon + 1, itLineEnd);
	trim(value, WHITE_SPACES);

	state.request.headers[key] = value;
}

void Parser::parseContentLength(State &state)
{
	std::map<std::string, std::string>::const_iterator it =
		state.request.headers.find(header::LOWER_CONTENT_LENGTH);

	if (it == state.request.headers.end())
	{
		if (expectsBody(state.request.method))
			throw Exception(Exception::contentLengthRequired);
		return;
	}

	std::string content_length = it->second;
	if (content_length.empty())
		throw Exception(Exception::contentLengthInvalid);

	char *endptr;
	errno = 0;
	unsigned long val = std::strtoul(content_length.c_str(), &endptr, 10);

	if (errno == ERANGE || *endptr != '\0' || content_length[0] == '-')
		throw Exception(Exception::contentLengthInvalid);
	if (val > _maxBodySize)
		throw Exception(Exception::bodyTooLarge);
	state.request.contentLength = static_cast<size_t>(val);
}

void Parser::parseBody(std::vector<char> const &inputBuf, State &state)
{
	state.bodyBytesRead += inputBuf.size();
	if (state.bodyBytesRead > _maxBodySize)
		throw Exception(Exception::bodyTooLarge);
	state.request.body.append(inputBuf);
}

std::string Parser::extractMethod(
	std::vector<char>::const_iterator &it, std::vector<char>::const_iterator itLineEnd
)
{
	std::vector<char>::const_iterator it_method_end =
		std::find_first_of(it, itLineEnd, WHITE_SPACES, WHITE_SPACES + sizeof(WHITE_SPACES) - 1);
	if (it_method_end == itLineEnd)
		throw Exception(Exception::requestLineMalformed);

	std::string method(it, it_method_end);
	if (!isMethodSupported(method))
		throw Exception(Exception::methodInvalid);

	it = it_method_end;
	return (method);
}

void Parser::extractTargetandQuery(
	std::vector<char>::const_iterator &it, std::vector<char>::const_iterator itLineEnd, State &state
)
{
	std::vector<char>::const_iterator it_target_start =
		std::find_if(it, itLineEnd, is_not_white_spaces);
	if (it_target_start == itLineEnd)
		throw Exception(Exception::requestLineMalformed);

	std::vector<char>::const_iterator it_target_end = std::find_first_of(
		it_target_start, itLineEnd, WHITE_SPACES, WHITE_SPACES + sizeof(WHITE_SPACES) - 1
	);
	if (it_target_end == itLineEnd)
		throw Exception(Exception::requestLineMalformed);

	if (!is_valid_target_syntax(it_target_start, it_target_end))
		throw Exception(Exception::targetInvalid);

	std::vector<char>::const_iterator it_query = std::find(it_target_start, it_target_end, '?');

	if (it_query != it_target_end)
	{
		state.request.target = std::string(it_target_start, it_query);
		state.request.query = std::string(it_query + 1, it_target_end);
	}
	else
		state.request.target = std::string(it_target_start, it_target_end);

	it = it_target_end;
}

std::string Parser::extractProtocol(
	std::vector<char>::const_iterator &it, std::vector<char>::const_iterator itLineEnd
)
{
	std::vector<char>::const_iterator it_protocol_start =
		std::find_if(it, itLineEnd, is_not_white_spaces);
	if (it_protocol_start == itLineEnd)
		throw Exception(Exception::requestLineMalformed);

	std::vector<char>::const_iterator it_protocol_end = std::find_first_of(
		it_protocol_start, itLineEnd, WHITE_SPACES, WHITE_SPACES + sizeof(WHITE_SPACES) - 1
	);

	std::string protocol(it_protocol_start, it_protocol_end);

	if (protocol != _httpVersionProvider.getHttpVersion())
		throw Exception(Exception::versionInvalid);
	it = it_protocol_end;
	return (protocol);
}

bool Parser::hasLineBreak(
	std::vector<char>::const_iterator itStart, std::vector<char>::const_iterator itEnd
)
{
	return ((std::find_first_of(itStart, itEnd, CRLF, CRLF + sizeof(CRLF) - 1) != itEnd));
}

std::vector<char>::iterator Parser::findCRLF(std::vector<char> &inputBuf)
{
	return (std::search(inputBuf.begin(), inputBuf.end(), CRLF, CRLF + sizeof(CRLF) - 1));
}

void Parser::validateRequestLineSize(std::size_t size)
{
	if (size > _maxRequestLineSize)
		throw Exception(Exception::requestLineTooLarge);
}

void Parser::validateHeaderLineSize(std::size_t size)
{
	if (size > _maxHeaderLineSize)
		throw Exception(Exception::requestLineTooLarge);
}

void Parser::validateHeaderCount(std::size_t count)
{
	if (count > _maxHeaderCount)
		throw Exception(Exception::headerCountTooLarge);
}

Parser::State::State(void) : step(start), currenLineSize(0), currentHeaderCount(0), bodyBytesRead(0)
{}

void Parser::State::reset(void)
{
	step = start;
	request.reset();
	currenLineSize = 0;
	currentHeaderCount = 0;
	bodyBytesRead = 0;
}

} // namespace request
} // namespace http
