/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiResponseMapper.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 21:05:23 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/08 22:02:14 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/mappers/CgiResponseMapper.hpp"
#include "cgi/Response.hpp"
#include "infrastructure/http/response/Response.hpp"

namespace http {

Response CgiResponseMapper::toHttpResponse(cgi::Response const &cgiResponse)
{
	Response::Builder builder;

	builder.withStatusCode(cgiResponse.getStatusCode());
	builder.withStatusReason(cgiResponse.getStatusReason());
	builder.withHeaders(cgiResponse.getHeaders());

	return (builder.build());
}

} // namespace http
