/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 21:20:24 by alpayet           #+#    #+#             */
/*   Updated: 2026/04/28 22:09:44 by alpayet          ###   ########.fr       */
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

void	HttpRequest::parseStartLine(std::vector<char>::const_iterator it_start,
	std::vector<char>::const_iterator it_line_end)
{
	std::vector<char>::const_iterator	it_first_space;
	std::vector<char>::const_iterator	it_second_space;

	it_first_space = std::find(it_start, it_line_end, ' ');
	it_second_space = std::find(it_first_space + 1, it_line_end, ' ');

	std::string	method(it_start, it_first_space);
	std::string	target(it_first_space + 1, it_second_space);
	std::string	protocol(it_second_space + 1, it_line_end);
	this->_target = target;
	this->_protocol = protocol;
	this->_state = ParseState_Header;
}

void	HttpRequest::parseHeaderLine(std::vector<char>::const_iterator it_start,
	std::vector<char>::const_iterator it_line_end)
{
	if (it_start == it_line_end)
	{
		this->_state = ParseState_Body;
		return ;
	}
	std::vector<char>::const_iterator	it_colon;

	it_colon = std::find(it_start, it_line_end, ':');

	std::string	key(it_start, it_colon);
	std::string	value(it_colon + 1, it_line_end);

	this->_headers[key] = value;
	this->_state = ParseState_Header;
}


IRequest::ParseState	HttpRequest::parse(std::vector<char> const &readBuf)
{
	std::vector<char>::const_iterator	it_start = readBuf.begin() + this->_pos;
	char const							needle[] = {'\r', '\n'};
	std::vector<char>::const_iterator	it_line_end = std::search(it_start,
		readBuf.end(), needle, needle + 2);

	if (it_line_end != readBuf.end())
	{
		if (this->_state == ParseState_StartLine)
			parseStartLine(it_start, it_line_end);
		if (this->_state == ParseState_Header)
			parseHeaderLine(it_start, it_line_end);
		this->_pos += std::distance(it_start, it_line_end) + 2;
	}
	return (this->_state);
}
