/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpTransaction.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:23:25 by alpayet           #+#    #+#             */
/*   Updated: 2026/04/29 23:11:20 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http/HttpTransaction.hpp"
#include "http/message/HttpRequest.hpp"
#include "http/parser/HttpRequestParser.hpp"

HttpTransaction::HttpTransaction(void)
{}

HttpTransaction::HttpTransaction(const HttpTransaction &src)
{
	*this = src;
}

HttpTransaction::~HttpTransaction(void)
{}

HttpTransaction	&HttpTransaction::operator=(HttpTransaction const &rhs)
{
	if (this != &rhs)
	{
		//
	}
	return (*this);
}

void	HttpTransaction::onDataReceived(std::vector<char> const &readBuf)
{
	if (this->_requestParser.getState() == HttpRequestParser::ParseState_Complete)
		requestBuilder();
}

void	HttpTransaction::requestBuilder(void)
{
	this->_request = new HttpRequest()
}