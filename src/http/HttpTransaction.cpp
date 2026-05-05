/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpTransaction.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:23:25 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/05 20:06:57 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http/HttpTransaction.hpp"
#include "http/message/HttpRequest.hpp"
#include "http/parser/HttpRequestParser.hpp"

HttpTransaction::HttpTransaction(void) :
	_request(NULL),
	_requestParser()
{}

HttpTransaction::HttpTransaction(const HttpTransaction &src) :
	_request((src._request) ? src._request->clone() : NULL),
	_requestParser(src._requestParser)
{}

HttpTransaction::~HttpTransaction(void)
{
	delete this->_request;
}

HttpTransaction	&HttpTransaction::operator=(HttpTransaction const &rhs)
{
	if (this != &rhs)
	{
		delete this->_request;
		this->_request = (rhs._request) ? rhs._request->clone() : NULL;
		this->_requestParser = rhs._requestParser;
	}
	return (*this);
}

void	HttpTransaction::onDataReceived(std::vector<char> const &readBuf)
{
	if (this->_requestParser.getState() == HttpRequestParser::complete)
		requestBuilder();
}

void	HttpTransaction::requestBuilder(void)
{
	this->_request = new HttpRequest(
		this->_requestParser.getMethod(),
		this->_requestParser.getTarget(),
		this->_requestParser.getProtocol(),
		this->_requestParser.getHeaders()
	);
	return ;
}
