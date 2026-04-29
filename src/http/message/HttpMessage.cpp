/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpMessage.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 22:57:54 by alpayet           #+#    #+#             */
/*   Updated: 2026/04/29 23:07:49 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpMessage.hpp"

HttpMessage::HttpMessage(void)
{}

HttpMessage::HttpMessage(std::map<std::string, std::string> const &headers) :
	_headers(headers)
{

}

HttpMessage::HttpMessage(const HttpMessage &src)
{
	*this = src;
}

HttpMessage::~HttpMessage(void)
{}

HttpMessage	&HttpMessage::operator=(HttpMessage const &rhs)
{
	if (this != &rhs)
	{
		//
	}
	return (*this);
}