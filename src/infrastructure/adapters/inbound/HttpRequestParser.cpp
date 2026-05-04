/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequestParser.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:40:42 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/04 18:14:10 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http/message/IRequest.hpp"
#include "infrastructure/adapters/inbound/HttpRequestParser.hpp"
#include "infrastructure/adapters/inbound/RequestMapper.hpp"
#include "domain/ports/inbound/IRequestInputPort.hpp"
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

HttpRequestParser::HttpRequestParser(IRequestInputPort *RequestInputPort) :
	_requestInputPort(RequestInputPort),
	_pos(0),
	_state(StartLine)
{}

HttpRequestParser::ParseState	HttpRequestParser::getState(void) const
{
	return (this->_state);
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
		if (this->_state == Complete)
		{
			RequestEntity	request_entity = RequestMapper::toDomain(this->_requestDto);
			this->_requestInputPort->handle(request_entity);
		}
		else
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

	// std::string	method(it_start, it_first_space);
	// this->_requestDto. = string_to_method(method);

	std::string	target(it_first_space + 1, it_second_space);
	this->_requestDto.target = target;

	std::string	protocol(it_second_space + 1, it_line_end);
	this->_requestDto.protocol = protocol;

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

	this->_requestDto.headers[key] = value;
}
