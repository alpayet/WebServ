/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestBuilder.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:10:40 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/30 01:41:16 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestBuilder.hpp"

RequestBuilder &RequestBuilder::withTarget(std::string const &target)
{
	_target = target;
	return (*this);
}

RequestBuilder &RequestBuilder::withProtocol(std::string const &protocol)
{
	_protocol = protocol;
	return (*this);
}

RequestBuilder &RequestBuilder::withHeaders(std::map<std::string, std::string> const &headers)
{
	_headers = headers;
	return (*this);
}

RequestEntity RequestBuilder::build(void) { return (RequestEntity(_target, _protocol, _headers)); }