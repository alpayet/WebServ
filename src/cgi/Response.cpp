/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 03:38:36 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/07 14:24:35 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgi/Response.hpp"

namespace cgi {
unsigned short const Response::StatusLine::DEFAULT_STATUS_CODE = 200;
char const			 Response::StatusLine::DEFAULT_REASON[] = "OK";
unsigned short const Response::StatusLine::DEFAULT_REDIR_STATUS_CODE = 302;
char const			 Response::StatusLine::DEFAULT_REDIR_REASON[] = "Found";
char const			 Response::BODY_NAME_TEMPLATE[] = "cgi_response_body";

Response::StatusLine::StatusLine(void)
	: statusCode(DEFAULT_STATUS_CODE), reason(DEFAULT_REASON), exists(false)
{}

void Response::StatusLine::reset(void)
{
	statusCode = DEFAULT_STATUS_CODE;
	reason = DEFAULT_REASON;
	exists = false;
}

Response::Location::Location(void) : uri() {}

void Response::Location::reset(void) { uri.clear(); }

Response::Response(void) : statusLine(), headers(), contentLength(-1), body(BODY_NAME_TEMPLATE) {}

void Response::reset(void)
{
	statusLine.reset();
	headers.clear();
	location.reset();
	contentLength = -1;
	body.reset();
}
} // namespace cgi