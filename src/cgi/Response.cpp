/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 03:38:36 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/06 00:39:44 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgi/Response.hpp"

namespace cgi {
unsigned short const Response::StatusLine::DEFAULT_STATUS_CODE = 200;
char const			 Response::StatusLine::DEFAULT_REASON[] = "OK";

Response::StatusLine::StatusLine(void)
	: statusCode(DEFAULT_STATUS_CODE), reason(DEFAULT_REASON), exists(false)
{}

void Response::StatusLine::reset(void)
{
	statusCode = DEFAULT_STATUS_CODE;
	reason = DEFAULT_REASON;
	exists = false;
}

Response::Response(void) : statusLine(), headers(), contentLength(0) {}

void Response::reset(void)
{
	statusLine.reset();
	headers.clear();
	contentLength = 0;
}
} // namespace cgi