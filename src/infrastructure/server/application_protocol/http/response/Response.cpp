/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 06:01:36 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/04 19:55:52 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/response/Response.hpp"
#include "application/ports/SystemResourceInfo.hpp"
#include "infrastructure/server/application_protocol/http/response/get_default_body.hpp"
#include "infrastructure/server/application_protocol/http/response/get_status_reason.hpp"
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

unsigned short Response::getStatusCode(void) const { return (_statusLine.statusCode); }

std::string const &Response::getStatusReason(void) const { return (_statusLine.reason); }

std::vector<Response::Header> const &Response::getHeaders(void) const { return (_headers); }

std::size_t Response::getContentLength(void) const { return (_contentLength); }

std::vector<char> const &Response::getBody(void) const { return (_body); }

bool Response::hasBody(void) const { return (!_body.empty()); }

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

std::ostream &operator<<(std::ostream &lhs, Response const &rhs)
{
	lhs << "***HTTP RESPONSE***" << std::endl;

	lhs << "\tStatusLine:" << std::endl;
	lhs << "\t\tStatusCode:" << rhs.getStatusCode() << std::endl;
	lhs << "\t\tReason:" << rhs.getStatusReason() << std::endl;

	lhs << "\tHeaders:" << std::endl;
	for (std::vector<Response::Header>::const_iterator it = rhs.getHeaders().begin();
		 it != rhs.getHeaders().end(); ++it)
		lhs << "\t\t" << it->key << ':' << it->value << std::endl;

	lhs << "\tContentLength:" << rhs.getContentLength() << std::endl;

	lhs << "***END HTTP RESPONSE***" << std::endl;
	return (lhs);
}
} // namespace http
