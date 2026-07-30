/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 02:29:14 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/11 22:40:16 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgi/Parser.hpp"
#include "cgi/Exception.hpp"
#include "infrastructure/constants.hpp"
#include "infrastructure/parsing/IValidationPolicy.hpp"
#include "infrastructure/parsing/constants.hpp"
#include "infrastructure/parsing/header_parser.hpp"
#include "infrastructure/parsing/line_reader.hpp"
#include "infrastructure/parsing/utils.hpp"
#include <algorithm>

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

Parser::Parser(const parse::IValidationPolicy &validationPolicy) : _validationPolicy(validationPolicy)
{
	_maxRequestLineSize =
		std::min(_validationPolicy.getMaxRequestLineSize(), parse::DEFAULT_MAX_REQUEST_LINE_SIZE);

	_maxHeaderLineSize =
		std::min(_validationPolicy.getMaxHeaderLineSize(), parse::DEFAULT_MAX_HEADER_LINE_SIZE);

	_maxHeaderCount =
		std::min(_validationPolicy.getMaxHeaderCount(), parse::DEFAULT_MAX_HEADER_COUNT);

	_maxBodySize = std::min(_validationPolicy.getMaxBodySize(), parse::DEFAULT_MAX_BODY_SIZE);
}

Parser::Step Parser::parse(std::vector<char> &inputBuf, bool isCgiEof, Parser::State &state)
{
	bool can_continue = true;

	while (can_continue && (!inputBuf.empty() || isCgiEof))
	{
		switch (state.step)
		{
			case Parser::header:
			{
				std::vector<char>::const_iterator it_start = inputBuf.begin();
				std::vector<char>::const_iterator it_line_end = parse::find_line_end(inputBuf);

				state.currenLineSize = std::distance(it_start, it_line_end);
				validateHeaderLineSize(state.currenLineSize);

				if (it_line_end == inputBuf.end())
				{
					if (isCgiEof)
						throw Exception(Exception::prematureEof);
					can_continue = false;
					break;
				}

				++state.currentHeaderCount;
				validateHeaderCount(state.currentHeaderCount);

				if (it_start == it_line_end)
				{
					parseContentLength(state.response);
					parseStatus(state.response);
					parseLocation(state.response);
					classifyResponse(state.response);
					parse::consume_line(inputBuf);

					if (state.response.getType() == Response::localRedir ||
						state.response.getType() == Response::clientRedir)
					{
						state.step = Parser::complete;
						can_continue = false;
					}
					else
						state.step = Parser::body;
					break;
				}

				parseHeaderLine(it_start, it_line_end, state.response);
				parse::consume_line(inputBuf);
				break;
			}
			case Parser::body:
			{
				parseBody(inputBuf, state.response, state.bodyBytesRead);
				inputBuf.clear();

				if (isCgiEof && state.response.hasContentLength() &&
					state.bodyBytesRead < state.response.getContentLength())
					throw Exception(Exception::prematureEof);

				if (isCgiEof || (state.response.hasContentLength() &&
								 state.bodyBytesRead == state.response.getContentLength()))
				{
					state.response.setContentLength(state.bodyBytesRead);
					state.response.prepareForReading();
					state.step = Parser::complete;
					can_continue = false;
				}
				break;
			}
			default:
				can_continue = false;
				break;
		}
	}
	return (state.step);
}

void Parser::classifyResponse(Response &response)
{
	if (response.hasLocation())
	{
		switch (response.getLocationType())
		{
			case Response::Location::local:
				if (response.getHeadersSize() != 1)
					throw Exception(Exception::localRedirResponseMalformed);
				response.setType(Response::localRedir);
				break;
			case Response::Location::client:
				if (response.hasHeader(headers::CONTENT_TYPE))
					response.setType(Response::clientRedirDoc);
				else
					response.setType(Response::clientRedir);

				response.setDefaultRedirStatus();
				break;
			default:
				break;
		}
	}
	else
	{
		if (!response.hasHeader(headers::CONTENT_TYPE))
			throw Exception(Exception::documentResponseMalformed);
		response.setType(Response::document);
	}
}

void Parser::parseHeaderLine(
	std::vector<char>::const_iterator itStart,
	std::vector<char>::const_iterator itLineEnd,
	Response						 &response
)
{
	std::string key, value;

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
	if (key == headers::SET_COOKIE)
		response.setCookie(value);
	else
		response.setHeader(key, value);
}

void Parser::parseStatus(Response &response)
{
	std::string const &status = response.getHeader(headers::STATUS);

	if (status.empty())
		return;

	std::string::const_iterator it_status_code_end =
		parse::find_white_spaces(status.begin(), status.end());

	if (it_status_code_end == status.end())
		throw Exception(Exception::statusCodeInvalid);

	std::string status_code(status.begin(), it_status_code_end);

	char *endptr = NULL;
	errno = 0;
	unsigned long val = std::strtoul(status_code.c_str(), &endptr, 10);

	if (errno == ERANGE || *endptr != '\0' || status_code[0] == '-')
		throw Exception(Exception::statusCodeInvalid);
	if (val < 100 || val > 599)
		throw Exception(Exception::statusCodeInvalid);

	std::string::const_iterator it_reason_start =
		std::find_if(it_status_code_end, status.end(), parse::is_not_white_spaces);

	std::string reason(it_reason_start, status.end());

	response.setStatus(static_cast<unsigned short>(val), reason);
}

void Parser::parseLocation(Response &response)
{
	std::string const &location = response.getHeader(headers::LOCATION);

	if (location.empty())
		return;

	if (!parse::is_valid_uri_syntax(location.begin(), location.end()))
		throw Exception(Exception::locationInvalid);

	std::string		  uri, query;
	std::size_t const query_pos = location.find(parse::QUERY_DELIMITER);

	if (query_pos != std::string::npos)
	{
		uri = std::string(location.begin(), location.begin() + query_pos);
		query = location.substr(query_pos + 1);
	}
	else
		uri = location;

	Response::Location::Type location_type =
		(uri[0] == '/') ? Response::Location::local : Response::Location::client;

	response.setLocation(uri, query, location_type);
}

void Parser::parseContentLength(Response &response)
{
	std::size_t content_length;

	switch (parse::parse_content_length(response.getHeaders(), _maxBodySize, content_length))
	{
		case parse::ParseContentLength::contentLengthMissing:
			return;
		case parse::ParseContentLength::contentLengthInvalid:
			throw Exception(Exception::contentLengthInvalid);
		case parse::ParseContentLength::bodyTooLarge:
			throw Exception(Exception::bodyTooLarge);
		default:
			break;
	}
	response.setContentLength(content_length);
}

void Parser::parseBody(
	std::vector<char> const &inputBuf, Response &response, std::size_t &bodyBytesRead
)
{
	validateBodySize(bodyBytesRead + inputBuf.size());

	if (response.hasContentLength() &&
		bodyBytesRead + inputBuf.size() > response.getContentLength())
		throw Exception(Exception::bodySizeMismatch);

	bodyBytesRead += response.appendBody(inputBuf);
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
