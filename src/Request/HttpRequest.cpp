/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 21:20:24 by alpayet           #+#    #+#             */
/*   Updated: 2026/04/19 21:20:32 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpRequest.hpp"

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