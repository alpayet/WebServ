/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpTransaction.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:23:25 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/30 01:41:16 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http/HttpTransaction.hpp"
#include "http/message/HttpRequest.hpp"
#include "http/parser/HttpRequestParser.hpp"

HttpTransaction::HttpTransaction(void) : _request(NULL), _requestParser() {}

HttpTransaction::HttpTransaction(const HttpTransaction &src)
	: _request((src._request) ? src._request->clone() : NULL), _requestParser(src._requestParser)
{
}

HttpTransaction::~HttpTransaction(void) { delete _request; }

HttpTransaction &HttpTransaction::operator=(HttpTransaction const &rhs)
{
	if (this != &rhs)
	{
		delete _request;
		_request = (rhs._request) ? rhs._request->clone() : NULL;
		_requestParser = rhs._requestParser;
	}
	return (*this);
}

void HttpTransaction::onDataReceived(std::vector<char> const &readBuf)
{
	if (_requestParser.getState() == HttpRequestParser::complete)
		requestBuilder();
}

void HttpTransaction::requestBuilder(void)
{
	_request = new HttpRequest(
		_requestParser.getMethod(), _requestParser.getTarget(), _requestParser.getProtocol(),
		_requestParser.getHeaders()
	);
	return;
}
