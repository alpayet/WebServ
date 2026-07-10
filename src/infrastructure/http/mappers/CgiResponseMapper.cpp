/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiResponseMapper.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 21:05:23 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/09 02:57:04 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/mappers/CgiResponseMapper.hpp"
#include "cgi/Response.hpp"
#include "infrastructure/http/response/Response.hpp"
#include "infrastructure/parsing/constants.hpp"

namespace http {

Response CgiResponseMapper::toHttpResponse(cgi::Response const &cgiResponse)
{
	Response::Builder builder;

	builder.withStatusCode(cgiResponse.getStatusCode());
	builder.withStatusReason(cgiResponse.getStatusReason());
	builder.withContentLength(cgiResponse.getContentLength());
	for (std::map<std::string, std::string>::const_iterator i = cgiResponse.getHeaders().begin();
		 i != cgiResponse.getHeaders().end(); ++i)
	{
		if (i->first != parse::STATUS && i->first != parse::CONTENT_LENGTH)
			builder.withHeader(i->first, i->second);
	}
	return (builder.build());
}

} // namespace http
