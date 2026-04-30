/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequestParser.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:40:42 by alpayet           #+#    #+#             */
/*   Updated: 2026/04/30 21:29:43 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http/parser/HttpRequestParser.hpp"
#include "http/message/IRequest.hpp"
#include <algorithm>

namespace
{
	IRequest::MethodType	string_to_method(std::string const &method_str)
	{
		if (method_str == "GET")
			return (IRequest::Get);
		if (method_str == "POST")
			return (IRequest::Post);
		if (method_str == "DELETE")
			return (IRequest::Delete);
		return (IRequest::Unknown);
	}
}

HttpRequestParser::HttpRequestParser(void) :
	_pos(0),
	_state(StartLine),
	_method(),
	_target(),
	_protocol(),
	_headers()
{}

HttpRequestParser::HttpRequestParser(const HttpRequestParser &src) :
	_pos(src._pos),
	_state(src._state),
	_method(src._method),
	_target(src._target),
	_protocol(src._protocol),
	_headers(src._headers)
{}

HttpRequestParser	&HttpRequestParser::operator=(HttpRequestParser const &rhs)
{
	if (this != &rhs)
	{
		this->_pos = rhs._pos;
		this->_state = rhs._state;
		this->_method = rhs._method;
		this->_target = rhs._target;
		this->_protocol = rhs._protocol;
		this->_headers = rhs._headers;
	}
	return (*this);
}

HttpRequestParser::ParseState	HttpRequestParser::getState(void) const
{
	return (this->_state);
}

IRequest::MethodType	HttpRequestParser::getMethod(void) const
{
	return (this->_method);
}

std::string const	&HttpRequestParser::getTarget(void) const
{
	return (this->_target);
}

std::string const	&HttpRequestParser::getProtocol(void) const
{
	return (this->_protocol);
}

std::map<std::string, std::string> const	&HttpRequestParser::getHeaders(void) const
{
	return (this->_headers);
}

HttpRequestParser::ParseState	HttpRequestParser::parse(std::vector<char> const &readBuf)
{
	std::vector<char>::const_iterator	it_start = readBuf.begin() + this->_pos;
	char const							needle[] = {'\r', '\n'};
	std::vector<char>::const_iterator	it_line_end = std::search(it_start,
		readBuf.end(), needle, needle + 2);

	if (it_line_end != readBuf.end())
	{
		switch (this->_state)
		{
			case StartLine:
				parseStartLine(it_start, it_line_end);
				break;
			case Header:
				parseHeaderLine(it_start, it_line_end);
				break;
			default:
				break;
		}
		this->_pos += std::distance(it_start, it_line_end) + 2;
	}
	return (this->_state);
}

void	HttpRequestParser::parseStartLine(std::vector<char>::const_iterator it_start,
	std::vector<char>::const_iterator it_line_end)
{
	std::vector<char>::const_iterator	it_first_space;
	std::vector<char>::const_iterator	it_second_space;

	it_first_space = std::find(it_start, it_line_end, ' ');
	it_second_space = std::find(it_first_space + 1, it_line_end, ' ');

	std::string	method(it_start, it_first_space);
	this->_method = string_to_method(method);

	std::string	target(it_first_space + 1, it_second_space);
	this->_target = target;

	std::string	protocol(it_second_space + 1, it_line_end);
	this->_protocol = protocol;

	this->_state = Header;
}

void	HttpRequestParser::parseHeaderLine(std::vector<char>::const_iterator it_start,
	std::vector<char>::const_iterator it_line_end)
{
	if (it_start == it_line_end)
	{
		this->_state = Body;
		return ;
	}
	std::vector<char>::const_iterator	it_colon;

	it_colon = std::find(it_start, it_line_end, ':');

	std::string	key(it_start, it_colon);
	std::string	value(it_colon + 1, it_line_end);

	this->_headers[key] = value;
}
