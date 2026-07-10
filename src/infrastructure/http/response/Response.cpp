/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 06:01:36 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/08 22:47:12 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/response/Response.hpp"
#include "application/ports/SystemResourceInfo.hpp"
#include "infrastructure/http/constants.hpp"
#include "infrastructure/http/response/get_default_body.hpp"
#include "infrastructure/http/response/get_status_reason.hpp"
#include <cstring>
#include <sstream>

namespace http {

unsigned short const Response::StatusLine::DEFAULT_STATUS_CODE = 200;
char const			 Response::StatusLine::DEFAULT_REASON[] = "OK";

Response::StatusLine::StatusLine(void) : statusCode(DEFAULT_STATUS_CODE), reason(DEFAULT_REASON) {}

void Response::StatusLine::reset(void)
{
	statusCode = DEFAULT_STATUS_CODE;
	reason = DEFAULT_REASON;
}

Response::Response(void) : _statusLine(), _headers(), _contentLength(0), _body() {}

unsigned short	   Response::getStatusCode(void) const { return (_statusLine.statusCode); }
std::string const &Response::getStatusReason(void) const { return (_statusLine.reason); }
std::vector<Response::Header> const &Response::getHeaders(void) const { return (_headers); }
std::size_t				 Response::getContentLength(void) const { return (_contentLength); }
std::vector<char> const &Response::getBody(void) const { return (_body); }
bool					 Response::hasBody(void) const { return (!_body.empty()); }

Response Response::buildErrorPage(
	unsigned short StatusErrorCode, app::SystemResourceInfo const &errorPageInfo
)
{
	Response::Builder builder;

	builder.withStatusLine(StatusErrorCode);
	builder.withContentLength(errorPageInfo.resourceSize);
	return (builder.build());
}

Response Response::buildDefault(unsigned short statusCode)
{
	char const		 *default_body = get_default_body(statusCode);
	Response::Builder builder;

	builder.withStatusLine(statusCode);
	builder.withContentLength(std::strlen(default_body));
	builder.withBody(default_body);
	return (builder.build());
}

void Response::reset(void)
{
	_statusLine.reset();
	_headers.clear();
	_contentLength = 0;
	_body.clear();
}
} // namespace http
