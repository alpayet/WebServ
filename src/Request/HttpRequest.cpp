/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 21:20:24 by alpayet           #+#    #+#             */
/*   Updated: 2026/04/21 21:26:59 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpRequest.hpp"
#include <algorithm>

HttpRequest::HttpRequest(void)
{}

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

IRequest::ParseState	HttpRequest::parse(std::vector<char> const &readBuf)
{
	std::vector<char>::const_iterator it;
	char const needle[] = {'\r', '\n'};

	it = std::search(readBuf.begin() + this->_pos, readBuf.end(), needle, needle + 2);
	if (it != readBuf.end())
		//
	return (this->_state);
}