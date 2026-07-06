/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 02:29:14 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/07 00:39:25 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgi/Parser.hpp"
#include "cgi/Exception.hpp"
#include "infrastructure/parsing/IValidationPolicy.hpp"
#include "infrastructure/parsing/constants.hpp"
#include "infrastructure/parsing/utils.hpp"

namespace cgi {
Parser::State::State(void)
	: step(header), response(), currenLineSize(0), currentHeaderCount(0), bodyBytesRead(0)
{}

void Parser::State::reset(void)
{
	step = header;
	response.reset();
	currenLineSize = 0;
	currentHeaderCount = 0;
	bodyBytesRead = 0;
}

Parser::Parser(parse::IValidationPolicy &validationPolicy) : _validationPolicy(validationPolicy)
{
	_maxRequestLineSize =
		std::min(_validationPolicy.getMaxRequestLineSize(), parse::DEFAULT_MAX_REQUEST_LINE_SIZE);

	_maxHeaderLineSize =
		std::min(_validationPolicy.getMaxHeaderLineSize(), parse::DEFAULT_MAX_HEADER_LINE_SIZE);

	_maxHeaderCount =
		std::min(_validationPolicy.getMaxHeaderCount(), parse::DEFAULT_MAX_HEADER_COUNT);

	_maxBodySize = std::min(_validationPolicy.getMaxBodySize(), parse::DEFAULT_MAX_BODY_SIZE);
}

Parser::Step Parser::parse(std::vector<char> &inputBuf, Parser::State &state)
{
	bool can_continue = true;

	while (can_continue && !inputBuf.empty())
	{
		switch (state.step)
		{
			case Parser::header:
			{
				std::vector<char>::const_iterator it_start = inputBuf.begin();
				std::vector<char>::const_iterator it_line_end = parse::find_line_end(inputBuf);

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
					if (state.response.contentLength != 0 &&
						expects_body(state.response.startLine.method))
						state.step = Parser::body;
					else
					{
						state.step = Parser::complete;
						can_continue = false;
					}
					parse::consume_line(inputBuf);
					break;
				}
				parseHeaderLine(it_start, it_line_end, state.response.headers);
				parseContentLength(state.response);

				parse::consume_line(inputBuf);
				state.currenLineSize = 0;
				break;
			}
			case Parser::body:
			{
				parseBody(inputBuf, state.response, state.bodyBytesRead);
				inputBuf.clear();
				if (state.bodyBytesRead == state.response.contentLength)
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

void classifyResponse(Response &response, Parser::Step &step)
{
	if (response.location.exists)
	{
		switch (response.location.type)
		{
			case Response::Location::local:
				if (response.headers.size() != 1)
					throw Exception(Exception::localRedirResponseMalformed);
				response.type = Response::localRedir;
				step = Parser::complete;
				break;

			case Response::Location::client:
				if (response.headers.find(parse::header::LOWER_CONTENT_TYPE) !=
					response.headers.end())
				{
					if (response.statusLine.size() != 1)
						throw Exception(Exception::localRedirResponseMalformed);
					response.type = Response::clientRedirDoc;
				}
				if (response.statusLine.exists)
					throw Exception(Exception::clientRedirResponseMalformed);
				response.statusLine.statusCode = 302;
				response.statusLine.reason = "Found";
				step = Parser::complete;
				break;

			default:
				break;
		}
	}
	response.type = Response::localRedir;
}

void parseHeaderLine(
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

void Parser::parseContentLength(Response &response)
{
	switch (parse::parse_content_length(response.headers, _maxBodySize, response.contentLength))
	{
		case parse::ParseContentLength::contentLengthInvalid:
			throw Exception(Exception::contentLengthInvalid);
		case parse::ParseContentLength::bodyTooLarge:
			throw Exception(Exception::bodyTooLarge);
		default:
			break;
	}
}

void Parser::parseBody(
	std::vector<char> const &inputBuf, Response &response, std::size_t &bodyBytesRead
)
{
	validateBodySize(bodyBytesRead + inputBuf.size());

	if (response.contentLength >= 0 && bodyBytesRead + inputBuf.size() > response.contentLength)
		throw Exception(Exception::bodyTooLarge);
	bodyBytesRead += response.body.write(inputBuf);
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
} // namespace cgi
