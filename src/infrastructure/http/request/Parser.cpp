/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:40:42 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/07 16:35:10 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/request/Parser.hpp"
#include "infrastructure/http/IHttpVersionProvider.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"
#include "infrastructure/http/methods.hpp"
#include "infrastructure/parsing/IValidationPolicy.hpp"
#include "infrastructure/parsing/constants.hpp"
#include "infrastructure/parsing/utils.hpp"
#include <algorithm>
#include <cerrno>

namespace {
bool is_invalid_target_char(unsigned char c) { return (c <= 32 || c == 127); }

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
} // namespace

namespace http {
namespace request {

Parser::State::State(void)
	: step(start), request(), currenLineSize(0), currentHeaderCount(0), bodyBytesRead(0)
{}

void Parser::State::reset(void)
{
	step = start;
	request.reset();
	currenLineSize = 0;
	currentHeaderCount = 0;
	bodyBytesRead = 0;
}

Parser::Parser(
	parse::IValidationPolicy &validationPolicy, IHttpVersionProvider &httpVersionProvider
)
	: _validationPolicy(validationPolicy), _httpVersionProvider(httpVersionProvider)
{
	_maxRequestLineSize =
		std::min(_validationPolicy.getMaxRequestLineSize(), parse::DEFAULT_MAX_REQUEST_LINE_SIZE);

	_maxHeaderLineSize =
		std::min(_validationPolicy.getMaxHeaderLineSize(), parse::DEFAULT_MAX_HEADER_LINE_SIZE);

	_maxHeaderCount =
		std::min(_validationPolicy.getMaxHeaderCount(), parse::DEFAULT_MAX_HEADER_COUNT);

	_maxBodySize = std::min(_validationPolicy.getMaxBodySize(), parse::DEFAULT_MAX_BODY_SIZE);
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
				std::vector<char>::const_iterator it_start = inputBuf.begin();
				std::vector<char>::const_iterator it_line_end = parse::find_line_end(inputBuf);

				if (it_start == it_line_end)
				{
					state.currenLineSize += 1;
					validateRequestLineSize(state.currenLineSize);

					parse::consume_line(inputBuf);
					break;
				}

				if (*it_start == parse::CR && it_start + 1 == inputBuf.end())
				{
					can_continue = false;
					break;
				}

				state.step = Parser::requestLine;
				break;
			}
			case Parser::requestLine:
			{
				std::vector<char>::const_iterator it_start = inputBuf.begin();
				std::vector<char>::const_iterator it_line_end = parse::find_line_end(inputBuf);

				state.currenLineSize = std::distance(it_start, it_line_end);
				validateRequestLineSize(state.currenLineSize);

				if (it_line_end == inputBuf.end())
				{
					can_continue = false;
					break;
				}

				parseRequestLine(it_start, it_line_end, state.request.startLine);

				parse::consume_line(inputBuf);
				state.currenLineSize = 0;
				state.step = Parser::header;
				break;
			}
			case Parser::header:
			{
				std::vector<char>::const_iterator it_start = inputBuf.begin();
				std::vector<char>::const_iterator it_line_end = parse::find_line_end(inputBuf);

				state.currenLineSize = std::distance(it_start, it_line_end);
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
					if (state.request.contentLength != 0 &&
						expects_body(state.request.startLine.method))
						state.step = Parser::body;
					else
					{
						state.step = Parser::complete;
						can_continue = false;
					}
					parse::consume_line(inputBuf);
					break;
				}

				parseHeaderLine(it_start, it_line_end, state.request.headers);
				parseContentLength(state.request);

				parse::consume_line(inputBuf);
				break;
			}
			case Parser::body:
			{
				parseBody(inputBuf, state.request, state.bodyBytesRead);
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
	Request::StartLine				 &startLine
)
{
	if (parse::has_line_break(itStart, itLineEnd))
		throw Exception(Exception::lineBreakInvalid);

	std::vector<char>::const_iterator it = itStart;

	startLine.method = extractMethod(it, itLineEnd);
	extractTargetandQuery(it, itLineEnd, startLine.target, startLine.query);
	startLine.protocol = extractProtocol(it, itLineEnd);

	if (std::find_if(it, itLineEnd, parse::is_not_white_spaces) != itLineEnd)
		throw Exception(Exception::requestLineMalformed);
}

void Parser::parseHeaderLine(
	std::vector<char>::const_iterator	itStart,
	std::vector<char>::const_iterator	itLineEnd,
	std::map<std::string, std::string> &headers
)
{
	std::string key;
	std::string value;

	switch (parse::parse_header_line(itStart, itLineEnd, key, value))
	{
		case parse::ParseHeaderLine::lineBreakInvalid:
			throw Exception(Exception::lineBreakInvalid);
		case parse::ParseHeaderLine::malformed:
			throw Exception(Exception::headerLineMalformed);
		case parse::ParseHeaderLine::keyInvalid:
			throw Exception(Exception::headerKeyInvalid);
		case parse::ParseHeaderLine::valueInvalid:
			throw Exception(Exception::headerValueInvalid);
		default:
			break;
	}
	headers[key] = value;
}

void Parser::parseContentLength(Request &request)
{
	switch (parse::parse_content_length(request.headers, _maxBodySize, request.contentLength))
	{
		case parse::ParseContentLength::contentLengthMissing:
			if (expects_body(request.startLine.method))
				throw Exception(Exception::contentLengthRequired);
			break;
		case parse::ParseContentLength::contentLengthInvalid:
			throw Exception(Exception::contentLengthInvalid);
		case parse::ParseContentLength::bodyTooLarge:
			throw Exception(Exception::bodyTooLarge);
		default:
			break;
	}
}

void Parser::parseBody(
	std::vector<char> const &inputBuf, Request &request, std::size_t &bodyBytesRead
)
{
	validateBodySize(bodyBytesRead + inputBuf.size());

	if (bodyBytesRead + inputBuf.size() > request.contentLength)
	{
		request.body.write(inputBuf, request.contentLength - bodyBytesRead);
		bodyBytesRead = request.contentLength;
	}
	else
		bodyBytesRead += request.body.write(inputBuf);
}

std::string Parser::extractMethod(
	std::vector<char>::const_iterator &it, std::vector<char>::const_iterator itLineEnd
)
{
	std::vector<char>::const_iterator it_method_end = parse::find_white_spaces(it, itLineEnd);
	if (it_method_end == itLineEnd)
		throw Exception(Exception::requestLineMalformed);

	std::string method(it, it_method_end);
	if (!is_method_supported(method))
		throw Exception(Exception::methodInvalid);

	it = it_method_end;
	return (method);
}

void Parser::extractTargetandQuery(
	std::vector<char>::const_iterator &it,
	std::vector<char>::const_iterator  itLineEnd,
	std::string						  &target,
	std::string						  &query
)
{
	std::vector<char>::const_iterator it_target_start =
		std::find_if(it, itLineEnd, parse::is_not_white_spaces);
	if (it_target_start == itLineEnd)
		throw Exception(Exception::requestLineMalformed);

	std::vector<char>::const_iterator it_target_end =
		parse::find_white_spaces(it_target_start, itLineEnd);
	if (it_target_end == itLineEnd)
		throw Exception(Exception::requestLineMalformed);

	if (!is_valid_target_syntax(it_target_start, it_target_end))
		throw Exception(Exception::targetInvalid);

	std::vector<char>::const_iterator it_query = std::find(it_target_start, it_target_end, '?');

	if (it_query != it_target_end)
	{
		target = std::string(it_target_start, it_query);
		query = std::string(it_query + 1, it_target_end);
	}
	else
		target = std::string(it_target_start, it_target_end);

	it = it_target_end;
}

std::string Parser::extractProtocol(
	std::vector<char>::const_iterator &it, std::vector<char>::const_iterator itLineEnd
)
{
	std::vector<char>::const_iterator it_protocol_start =
		std::find_if(it, itLineEnd, parse::is_not_white_spaces);
	if (it_protocol_start == itLineEnd)
		throw Exception(Exception::requestLineMalformed);

	std::vector<char>::const_iterator it_protocol_end =
		parse::find_white_spaces(it_protocol_start, itLineEnd);

	std::string protocol(it_protocol_start, it_protocol_end);

	if (protocol != _httpVersionProvider.getHttpVersion())
		throw Exception(Exception::versionInvalid);
	it = it_protocol_end;
	return (protocol);
}

void Parser::validateRequestLineSize(std::size_t size)
{
	if (size > _maxRequestLineSize)
		throw Exception(Exception::requestLineTooLarge);
}

void Parser::validateHeaderLineSize(std::size_t size)
{
	if (size > _maxHeaderLineSize)
		throw Exception(Exception::headerLineTooLarge);
}

void Parser::validateHeaderCount(std::size_t count)
{
	if (count > _maxHeaderCount)
		throw Exception(Exception::headerCountTooLarge);
}

void Parser::validateBodySize(std::size_t size)
{
	if (size > _maxBodySize)
		throw Exception(Exception::bodyTooLarge);
}

} // namespace request
} // namespace http
