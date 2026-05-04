/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestBuilder.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:10:40 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/04 17:09:57 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestBuilder.hpp"

RequestBuilder	&RequestBuilder::withTarget(std::string const &target)
{
	this->_target = target;
	return (*this);
}

RequestBuilder	&RequestBuilder::withProtocol(std::string const &protocol)
{
	this->_protocol = protocol;
	return (*this);
}

RequestBuilder	&RequestBuilder::withHeaders(
	std::map<std::string,std::string> const &headers)
{
	this->_headers = headers;
	return (*this);
}

RequestEntity	RequestBuilder::build(void)
{
	return (RequestEntity(this->_target, this->_protocol, this->_headers));
}