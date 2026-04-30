/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 21:20:24 by alpayet           #+#    #+#             */
/*   Updated: 2026/04/30 19:57:34 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpRequest.hpp"
#include <algorithm>

HttpRequest::HttpRequest(MethodType const method, std::string const &target,
	std::string const &protocol, std::map<std::string, std::string> const &headers) :
	IRequest(),
	HttpMessage(headers),
	_method(method),
	_target(target),
	_protocol(protocol)
{}

HttpRequest::HttpRequest(const HttpRequest &src) :
	IRequest(),
	HttpMessage(src),
	_method(this->_method),
	_target(this->_target),
	_protocol(this->_protocol)
{}

HttpRequest	&HttpRequest::operator=(HttpRequest const &rhs)
{
	if (this != &rhs)
	{
		HttpMessage::operator=(rhs);
		this->_method = rhs._method;
		this->_target = rhs._target;
		this->_protocol = rhs._protocol;
	}
	return (*this);
}


IRequest::MethodType	HttpRequest::getMethod(void) const
{
	return (this->_method);
}

std::string const	&HttpRequest::getTarget(void) const
{
	return (this->_target);
}

std::string const	&HttpRequest::getProtocol(void) const
{
	return (this->_protocol);
}

IRequest	*HttpRequest::clone(void) const
{
	return (new HttpRequest(*this));
}
