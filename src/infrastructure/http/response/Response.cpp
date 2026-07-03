/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 06:01:36 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/03 21:02:22 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/response/Response.hpp"
#include "application/ports/SystemResourceInfo.hpp"
#include "infrastructure/http/constants.hpp"
#include "infrastructure/http/exceptions/generateDefaultBody.hpp"
#include <cstring>
#include <sstream>

namespace http {

Response::Response(void) : statusCode(0), headers(), contentLength(0), body() {}

Response Response::buildErrorPage(
	unsigned short const StatusErrorCode, app::SystemResourceInfo const &errorPageInfo
)
{
	Response::Builder builder;

	builder.withStatusCode(StatusErrorCode);
	builder.withContentLength(errorPageInfo.resourceSize);
	return (builder.build());
}

Response Response::buildDefault(unsigned short const statusCode)
{
	char const		 *default_body = generateDefaultBody(statusCode);
	Response::Builder builder;

	builder.withStatusCode(statusCode);
	builder.withContentLength(std::strlen(default_body));
	builder.withBody(default_body);
	return (builder.build());
}

void Response::reset(void)
{
	headers.clear();
	contentLength = 0;
	body.clear();
}
} // namespace http
