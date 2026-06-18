/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseBuilder.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 21:10:16 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/18 21:58:02 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/messages/Response.hpp"

namespace http {
Response::Builder &Response::Builder::withProtocol(std::string const &protocol)
{
	_response.protocol = protocol;
}

Response::Builder &Response::Builder::withStatus(Response::Status const &status)
{
	_response.status = status;
	return (*this);
}
Response::Builder &Response::Builder::withHeader(std::string const &key, std::string const &value)
{
	Response::Header header = {.key = key, .value = value};
	_response.headers.insert(_response.headers.end(), header);
	return (*this);
}
Response::Builder &Response::Builder::withBody(std::vector<char> const &body)
{
	_response.body = body;
	return (*this);
}

Response const &Response::Builder::build(void) const { return (_response); }

} // namespace http
