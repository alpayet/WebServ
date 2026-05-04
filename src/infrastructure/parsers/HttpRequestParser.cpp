/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequestParser.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:40:42 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/05 00:07:11 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http/message/IRequest.hpp"
#include "infrastructure/parsers/HttpRequestParser.hpp"
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

	void	parseStartLine(std::vector<char>::const_iterator it_start,
		std::vector<char>::const_iterator it_line_end, ParsingContext &context)
	{
		std::vector<char>::const_iterator	it_first_space;
		std::vector<char>::const_iterator	it_second_space;

		it_first_space = std::find(it_start, it_line_end, ' ');
		it_second_space = std::find(it_first_space + 1, it_line_end, ' ');

		// std::string	method(it_start, it_first_space);
		// this->_requestDto. = string_to_method(method);

		std::string	target(it_first_space + 1, it_second_space);
		context.requestDto.target = target;

		std::string	protocol(it_second_space + 1, it_line_end);
		context.requestDto.protocol = protocol;

		context.state = ParsingContext::Header;
	}

	void	parseHeaderLine(std::vector<char>::const_iterator it_start,
		std::vector<char>::const_iterator it_line_end, ParsingContext &context)
	{
		if (it_start == it_line_end)
		{
			context.state = ParsingContext::Body;
			return ;
		}
		std::vector<char>::const_iterator	it_colon;

		it_colon = std::find(it_start, it_line_end, ':');

		std::string	key(it_start, it_colon);
		std::string	value(it_colon + 1, it_line_end);

		context.requestDto.headers[key] = value;
	}
}

ParsingContext::ParseState HttpRequestParser::parse(
	std::vector<char> const &readBuf, ParsingContext &context)
{
	std::vector<char>::const_iterator	it_start = readBuf.begin() + context.pos;
	char const							needle[] = {'\r', '\n'};
	std::vector<char>::const_iterator	it_line_end = std::search(it_start,
		readBuf.end(), needle, needle + 2);

	if (it_line_end != readBuf.end())
	{
		switch (context.state)
		{
			case ParsingContext::StartLine:
				parseStartLine(it_start, it_line_end);
				break;
			case ParsingContext::Header:
				parseHeaderLine(it_start, it_line_end);
				break;
			default:
				break;
		}
		// if (context.state == ParsingContext::Complete)
		// {
		// 	RequestEntity	request_entity = RequestMapper::toDomain(this->_requestDto);
		// 	this->_requestInputPort->handle(request_entity);
		// }
		context.pos += std::distance(it_start, it_line_end) + 2;
	}
	return (context.state);
}
