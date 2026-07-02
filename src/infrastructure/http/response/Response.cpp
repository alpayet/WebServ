/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 06:01:36 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/02 02:20:54 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/response/Response.hpp"

namespace http {

Response Response::buildFixed(unsigned short const statusCode)
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
