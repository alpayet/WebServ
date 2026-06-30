/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseBuilder.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 21:10:16 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/30 20:21:08 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/response/Response.hpp"

namespace http {

Response::Builder &Response::Builder::withStatusCode(unsigned short const statusCode)
{
	_response.statusCode = statusCode;
	return (*this);
}
Response::Builder &Response::Builder::withHeader(std::string const &key, std::string const &value)
{
	Response::Header header = {.key = key, .value = value};
	_response.headers.push_back(header);
	return (*this);
}
Response::Builder &Response::Builder::withBody(std::vector<char> const &body)
{
	_response.body = body;
	return (*this);
}

Response &Response::Builder::build(void) { return (_response); }

} // namespace http
