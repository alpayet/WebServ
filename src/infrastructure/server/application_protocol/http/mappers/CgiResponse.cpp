/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiResponse.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 21:05:23 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/09 22:21:47 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/mappers/CgiResponse.hpp"
#include "cgi/Response.hpp"
#include "infrastructure/server/application_protocol/constants.hpp"
#include "infrastructure/server/application_protocol/http/response/Response.hpp"

namespace http {
namespace mapper {

Response CgiResponse::toHttpResponse(cgi::Response const &cgiResponse)
{
	Response::Builder builder;

	builder.withStatusCode(cgiResponse.getStatusCode());
	builder.withStatusReason(cgiResponse.getStatusReason());
	builder.withContentLength(cgiResponse.getContentLength());

	for (std::map<std::string, std::string>::const_iterator it = cgiResponse.getHeaders().begin();
		 it != cgiResponse.getHeaders().end(); ++it)
	{
		if (it->first != headers::STATUS && it->first != headers::CONTENT_LENGTH)
			builder.withHeader(it->first, it->second);
	}

	for (std::vector<std::string>::const_iterator it = cgiResponse.getCookies().begin();
		 it != cgiResponse.getCookies().end(); ++it)
		builder.withHeader(headers::SET_COOKIE, *it);

	return (builder.build());
}

} // namespace mapper

} // namespace http
