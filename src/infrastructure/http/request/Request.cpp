/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 05:26:10 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/06 23:17:27 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/request/Request.hpp"

namespace http {
char const Request::BODY_NAME_TEMPLATE[] = "http_request_body";

void Request::StartLine::reset(void)
{
	method.clear();
	target.clear();
	query.clear();
	protocol.clear();
}
Request::Request() : headers(), contentLength(0), body(BODY_NAME_TEMPLATE) {}

void Request::reset(void)
{
	startLine.reset();
	headers.clear();
	contentLength = 0;
	body.reset();
}

} // namespace http
