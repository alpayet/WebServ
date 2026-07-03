/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 06:01:36 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/03 06:06:41 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/response/Response.hpp"
#include "application/ports/SystemResourceInfo.hpp"
#include "infrastructure/http/constants.hpp"
#include "infrastructure/http/exceptions/generateDefaultBody.hpp"
#include <cstring>
#include <sstream>

namespace http {

Response::Response(void) : statusCode(0), headers(), body() {}

Response Response::buildErrorPage(
	unsigned short const StatusErrorCode, app::SystemResourceInfo const &errorPageInfo
)
{
	std::stringstream content_length_ss;
	content_length_ss << errorPageInfo.resourceSize;

	Response::Builder builder;

	builder.withStatusCode(StatusErrorCode);
	builder.withHeader(http::header::CONTENT_LENGTH, content_length_ss.str());
	return (builder.build());
}

Response Response::buildDefault(unsigned short const statusCode)
{
	char const *default_body = generateDefaultBody(statusCode);

	std::stringstream content_length_ss;
	content_length_ss << std::strlen(default_body);

	Response::Builder builder;

	builder.withStatusCode(statusCode);
	builder.withHeader(http::header::CONTENT_LENGTH, content_length_ss.str());
	builder.withBody(default_body);
	return (builder.build());
}

void Response::reset(void)
{
	headers.clear();
	body.clear();
}
} // namespace http
