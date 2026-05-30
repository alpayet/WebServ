/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 21:20:24 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/30 01:41:16 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpRequest.hpp"
#include <algorithm>

HttpRequest::HttpRequest(
	MethodType const						  method,
	std::string const						 &target,
	std::string const						 &protocol,
	std::map<std::string, std::string> const &headers
)
	: IRequest(), HttpMessage(headers), _method(method), _target(target), _protocol(protocol)
{
}

HttpRequest::HttpRequest(const HttpRequest &src)
	: IRequest(), HttpMessage(src), _method(_method), _target(_target), _protocol(_protocol)
{
}

HttpRequest &HttpRequest::operator=(HttpRequest const &rhs)
{
	if (this != &rhs)
	{
		HttpMessage::operator=(rhs);
		_method = rhs._method;
		_target = rhs._target;
		_protocol = rhs._protocol;
	}
	return (*this);
}

IRequest::MethodType HttpRequest::getMethod(void) const { return (_method); }

std::string const &HttpRequest::getTarget(void) const { return (_target); }

std::string const &HttpRequest::getProtocol(void) const { return (_protocol); }

IRequest *HttpRequest::clone(void) const { return (new HttpRequest(*this)); }
