/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseBuilder.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 21:10:16 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/04 19:55:52 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/constants.hpp"
#include "infrastructure/server/application_protocol/http/exceptions/error_lookup.hpp"
#include "infrastructure/server/application_protocol/http/response/Response.hpp"
#include "infrastructure/server/application_protocol/http/response/get_default_body.hpp"
#include "infrastructure/server/application_protocol/http/response/get_status_reason.hpp"
#include <cstdlib>
#include <cstring>
#include <sstream>

namespace http {

Response::Builder &Response::Builder::withStatusCode(unsigned short statusCode)
{
	_response._statusLine.statusCode = statusCode;
	return (*this);
}

Response::Builder &Response::Builder::withStatusReason(std::string const &reason)
{
	_response._statusLine.reason = reason;
	return (*this);
}
Response::Builder &Response::Builder::withStatusLine(unsigned short statusCode)
{
	withStatusCode(statusCode);
	withStatusReason(get_status_reason(statusCode));
	return (*this);
}

Response::Builder &Response::Builder::withContentLength(std::size_t contentLength)
{
	withHeader(headers::CONTENT_LENGTH, contentLength);
	_response._contentLength = contentLength;
	return (*this);
}

Response::Builder &Response::Builder::withContentLength(std::string const &contentLength)
{
	char		 *endptr = NULL;
	unsigned long val = std::strtoull(contentLength.c_str(), &endptr, 10);

	withContentLength(static_cast<size_t>(val));
	return (*this);
}

Response::Builder &Response::Builder::withHeader(std::string const &key, std::string const &value)
{
	Response::Header header = {.key = key, .value = value};
	_response._headers.push_back(header);
	return (*this);
}

Response::Builder &Response::Builder::withHeader(std::string const &key, std::size_t value)
{
	std::stringstream value_ss;
	value_ss << value;

	Response::Header header = {.key = key, .value = value_ss.str()};
	_response._headers.push_back(header);
	return (*this);
}

Response::Builder &Response::Builder::withBody(std::vector<char> const &body)
{
	_response._body = body;
	return (*this);
}

Response::Builder &Response::Builder::withBody(std::string const &body)
{
	_response._body = std::vector<char>(body.begin(), body.end());
	return (*this);
}

Response::Builder &Response::Builder::withBody(char const *body)
{
	_response._body = std::vector<char>(body, body + std::strlen(body));
	return (*this);
}

Response &Response::Builder::build(void) { return (_response); }

} // namespace http
