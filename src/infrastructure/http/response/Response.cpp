/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 06:01:36 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/06 05:11:02 by alpayet          ###   ########.fr       */
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

Response::Response(void) : statusLine(), headers(), contentLength(0), body() {}

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
	statusLine.reset();
	headers.clear();
	contentLength = 0;
	body.clear();
}
} // namespace http
