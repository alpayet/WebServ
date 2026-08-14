/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:40:42 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/14 01:28:56 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/request/Parser.hpp"
#include <algorithm>
#include <cerrno>
#include "infrastructure/server/application_protocol/http/IHttpVersionProvider.hpp"
#include "infrastructure/server/application_protocol/http/exceptions/Exception.hpp"
#include "infrastructure/server/application_protocol/http/methods.hpp"
#include "infrastructure/server/application_protocol/parsing/IValidationPolicy.hpp"
#include "infrastructure/server/application_protocol/parsing/constants.hpp"
#include "infrastructure/server/application_protocol/parsing/header_parser.hpp"
#include "infrastructure/server/application_protocol/parsing/line_reader.hpp"
#include "infrastructure/server/application_protocol/parsing/utils.hpp"

namespace http {
	namespace request {

		Parser::State::State(void) : step(START), request(), currenLineSize(0), currentHeaderCount(0), bodyBytesRead(0)
		{}

		void Parser::State::reset(void)
		{
			step = START;
			request.reset();
			currenLineSize = 0;
			currentHeaderCount = 0;
			bodyBytesRead = 0;
		}

		Parser::Parser(const parse::IValidationPolicy& validationPolicy,
		               const IHttpVersionProvider& httpVersionProvider) :
		    _maxRequestLineSize(validationPolicy.getMaxRequestLineSize()),
		    _maxHeaderLineSize(validationPolicy.getMaxHeaderLineSize()),
		    _maxHeaderCount(validationPolicy.getMaxHeaderCount()), _maxBodySize(validationPolicy.getMaxBodySize()),
		    _httpVersionProvider(httpVersionProvider)
		{}

		Parser::Step Parser::parse(std::vector<char>& inputBuf, State& state)
		{
			bool can_continue = true;

			while (can_continue && !inputBuf.empty())
			{
				switch (state.step)
				{
				case Parser::START:
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

						state.step = Parser::REQUEST_LINE;
						break;
					}
				case Parser::REQUEST_LINE:
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

						parseRequestLine(it_start, it_line_end, state.request);
						parse::consume_line(inputBuf);
						state.currenLineSize = 0;
						state.step = Parser::HEADER;
						break;
					}
				case Parser::HEADER:
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
							parseContentLength(state.request);
							if (state.request.getContentLength() != 0 && expects_body(state.request.getMethod()))
								state.step = Parser::BODY;
							else
							{
								state.step = Parser::COMPLETE;
								can_continue = false;
							}
							parse::consume_line(inputBuf);
							break;
						}

						parseHeaderLine(it_start, it_line_end, state.request);
						parse::consume_line(inputBuf);
						break;
					}
				case Parser::BODY:
					{
						const std::size_t before = state.bodyBytesRead;
						parseBody(inputBuf, state.request, state.bodyBytesRead);
						const std::size_t consumed = state.bodyBytesRead - before;
						inputBuf.erase(
							inputBuf.begin(), inputBuf.begin() + static_cast<std::ptrdiff_t>(consumed)
						);

						if (state.bodyBytesRead == state.request.getContentLength())
						{
							state.request.prepareForReading();
							state.step = Parser::COMPLETE;
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

		void Parser::parseRequestLine(std::vector<char>::const_iterator itStart,
		                              std::vector<char>::const_iterator itLineEnd, Request& request)
		{
			if (parse::has_line_break(itStart, itLineEnd))
				throw Exception(Exception::LINE_BREAK_INVALID);

			std::vector<char>::const_iterator it = itStart;

			std::string method, target, query, protocol;

			method = extractMethod(it, itLineEnd);
			extractTargetandQuery(it, itLineEnd, target, query);
			protocol = extractProtocol(it, itLineEnd);

			if (std::find_if(it, itLineEnd, parse::is_not_white_spaces) != itLineEnd)
				throw Exception(Exception::REQUEST_LINE_MALFORMED);

			request.setStartLine(method, target, query, protocol);
		}

		void Parser::parseHeaderLine(std::vector<char>::const_iterator itStart,
		                             std::vector<char>::const_iterator itLineEnd, Request& request)
		{
			std::string key, value;

			switch (parse::parse_header_line(itStart, itLineEnd, key, value))
			{
			case parse::ParseHeaderLine::LINE_BREAK_INVALID:
				throw Exception(Exception::LINE_BREAK_INVALID);
			case parse::ParseHeaderLine::MALFORMED:
				throw Exception(Exception::HEADER_LINE_MALFORMED);
			case parse::ParseHeaderLine::KEY_INVALID:
				throw Exception(Exception::HEADER_KEY_INVALID);
			case parse::ParseHeaderLine::VALUE_INVALID:
				throw Exception(Exception::HEADER_VALUE_INVALID);
			default:
				break;
			}
			request.setHeader(key, value);
		}

		void Parser::parseContentLength(Request& request)
		{
			std::size_t content_length = 0;

			switch (parse::parse_content_length(request.getHeaders(), _maxBodySize, content_length))
			{
			case parse::ParseContentLength::NO_CONTENT_LENGTH:
				if (expects_body(request.getMethod()))
					throw Exception(Exception::CONTENT_LENGTH_REQUIRED);
				break;
			case parse::ParseContentLength::CONTENT_LENGTH_INVALID:
				throw Exception(Exception::CONTENT_LENGTH_INVALID);
			case parse::ParseContentLength::BODY_TOO_LARGE:
				throw Exception(Exception::BODY_TOO_LARGE);
			default:
				break;
			}
			request.setContentLength(content_length);
		}

		void Parser::parseBody(const std::vector<char>& inputBuf, Request& request, std::size_t& bodyBytesRead)
		{
			validateBodySize(bodyBytesRead + inputBuf.size());

			if (bodyBytesRead + inputBuf.size() > request.getContentLength())
			{
				request.appendBody(inputBuf, request.getContentLength() - bodyBytesRead);
				bodyBytesRead = request.getContentLength();
			}
			else
				bodyBytesRead += request.appendBody(inputBuf);
		}

		std::string Parser::extractMethod(std::vector<char>::const_iterator& it,
		                                  std::vector<char>::const_iterator itLineEnd)
		{
			std::vector<char>::const_iterator it_method_end = parse::find_white_spaces(it, itLineEnd);
			if (it_method_end == itLineEnd)
				throw Exception(Exception::REQUEST_LINE_MALFORMED);

			std::string method(it, it_method_end);
			if (!is_method_supported(method))
				throw Exception(Exception::METHOD_INVALID);

			it = it_method_end;
			return (method);
		}

		void Parser::extractTargetandQuery(std::vector<char>::const_iterator& it,
		                                   std::vector<char>::const_iterator itLineEnd, std::string& target,
		                                   std::string& query)
		{
			std::vector<char>::const_iterator it_target_start = std::find_if(it, itLineEnd, parse::is_not_white_spaces);
			if (it_target_start == itLineEnd)
				throw Exception(Exception::REQUEST_LINE_MALFORMED);

			std::vector<char>::const_iterator it_target_end = parse::find_white_spaces(it_target_start, itLineEnd);
			if (it_target_end == itLineEnd)
				throw Exception(Exception::REQUEST_LINE_MALFORMED);

			if (*it_target_start != '/')
				throw Exception(Exception::TARGET_INVALID);
			if (!parse::is_valid_uri_syntax(it_target_start, it_target_end))
				throw Exception(Exception::TARGET_INVALID);

			std::vector<char>::const_iterator it_query =
			    std::find(it_target_start, it_target_end, parse::QUERY_DELIMITER);

			if (it_query != it_target_end)
			{
				target = std::string(it_target_start, it_query);
				query = std::string(it_query + 1, it_target_end);
			}
			else
				target = std::string(it_target_start, it_target_end);

			parse::uri_decode(target);
			it = it_target_end;
		}

		std::string Parser::extractProtocol(std::vector<char>::const_iterator& it,
		                                    std::vector<char>::const_iterator itLineEnd)
		{
			std::vector<char>::const_iterator it_protocol_start =
			    std::find_if(it, itLineEnd, parse::is_not_white_spaces);
			if (it_protocol_start == itLineEnd)
				throw Exception(Exception::REQUEST_LINE_MALFORMED);

			std::vector<char>::const_iterator it_protocol_end = parse::find_white_spaces(it_protocol_start, itLineEnd);

			std::string protocol(it_protocol_start, it_protocol_end);

			if (!_httpVersionProvider.isSupportedHttpVersion(protocol))
				throw Exception(Exception::VERSION_INVALID);
			it = it_protocol_end;
			return (protocol);
		}

		void Parser::validateRequestLineSize(std::size_t size)
		{
			if (size > _maxRequestLineSize)
				throw Exception(Exception::REQUEST_LINE_TOO_LARGE);
		}

		void Parser::validateHeaderLineSize(std::size_t size)
		{
			if (size > _maxHeaderLineSize)
				throw Exception(Exception::HEADER_LINE_TOO_LARGE);
		}

		void Parser::validateHeaderCount(std::size_t count)
		{
			if (count > _maxHeaderCount)
				throw Exception(Exception::HEADER_COUNT_TOO_LARGE);
		}

		void Parser::validateBodySize(std::size_t size)
		{
			if (size > _maxBodySize)
				throw Exception(Exception::BODY_TOO_LARGE);
		}

	} // namespace request
} // namespace http
