/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 21:20:24 by alpayet           #+#    #+#             */
/*   Updated: 2026/04/29 23:09:11 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpRequest.hpp"
#include <algorithm>

HttpRequest::HttpRequest(void)
{}

HttpRequest::HttpRequest(MethodType const method, std::string const &target,
	std::string const &protocol, std::map<std::string, std::string> const &headers) :
	IRequest(),
	HttpMessage(headers),
	_method(method),
	_target(target),
	_protocol(protocol)
{

}

HttpRequest::HttpRequest(const HttpRequest &src)
{
	*this = src;
}

HttpRequest::~HttpRequest(void)
{}

HttpRequest	&HttpRequest::operator=(HttpRequest const &rhs)
{
	if (this != &rhs)
	{
		//
	}
	return (*this);
}

