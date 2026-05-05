/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequestParser.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:40:42 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/05 23:34:04 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http/message/IRequest.hpp"
#include "infrastructure/parsers/HttpRequestParser.hpp"
#include "infrastructure/exceptions/HttpException.hpp"
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

	void	parse_start_line(std::vector<char>::const_iterator it_start,
		std::vector<char>::const_iterator &it_line_end, ParsingContext context)
	{
		std::vector<char>::const_iterator	it_first_space;
		std::vector<char>::const_iterator	it_second_space;

		while (it_start[0] == '\r' && it_start[1] == '\n')
			it_start += 2;

		ensure_no_line_break(it_start, it_line_end - 1);

		it_first_space = std::find(it_start, it_line_end, ' ');
		if (it_first_space == it_line_end)
			throw HttpException(HttpException::malformedStartLine);
		it_second_space = std::find(it_first_space + 1, it_line_end, ' ');
		if (it_second_space == it_line_end)
			throw HttpException(HttpException::malformedStartLine);

		// std::string	method(it_start, it_first_space);
		// this->_requestDto. = string_to_method(method);

		std::string	target(it_first_space + 1, it_second_space);
		context.requestDto.target = target;

		std::string	protocol(it_second_space + 1, it_line_end);
		context.requestDto.protocol = protocol;

		context.state = ParsingContext::header;
	}

	void	parse_header_line(std::vector<char>::const_iterator it_start,
		std::vector<char>::const_iterator it_line_end, ParsingContext &context)
	{
		if (it_start == it_line_end)
		{
			context.state = ParsingContext::body;
			return ;
		}

		ensure_no_line_break(it_start, it_line_end - 1);

		std::vector<char>::const_iterator	it_colon;
		it_colon = std::find(it_start, it_line_end, ':');

		std::string	key(it_start, it_colon);
		if (key.find_first_of(" \t") != std::string::npos)
			throw HttpException(HttpException::invalidHeader);
		std::transform(key.begin(), key.end(), key.begin(), to_lower_safe);

		std::string	value(it_colon + 1, it_line_end);
		trim(value, " \t");
		if (key.find_first_of() != std::string::npos)
			throw HttpException(HttpException::invalidHeader);
		context.requestDto.headers[key] = value;
	}

	char	to_lower_safe(unsigned char c)
	{
		return (static_cast<char>(std::tolower(c)));
	}

	void trim(std::string &str, char const *to_trim)
	{
		std::size_t end = str.find_last_not_of(to_trim);
		if (end != std::string::npos)
			str.erase(end + 1);
		else
		{
			str.clear();
			return;
		}

		std::size_t start = str.find_first_not_of(to_trim);
		if (start != std::string::npos && start != 0)
			str.erase(0, start);
	}

	void ensure_no_line_break(std::vector<char>::const_iterator&it_start,
		std::vector<char>::const_iterator it_end)
	{
		static char const line_breakers[] = {'\r', '\n'};
		if (std::find_first_of(it_start, it_end,
			line_breakers, line_breakers + 2) != it_end)
			throw HttpException(HttpException::malformedLineBreak);
	}

	bool	is_valid_header_key_char()
	{

	}
}

ParsingContext::ParseState HttpRequestParser::parse(
	std::vector<char> const &readBuf, ParsingContext &context)
{
	std::vector<char>::const_iterator	it_start = readBuf.begin() + context.pos;
	static char const							needle[] = {'\r', '\n'};
	std::vector<char>::const_iterator	it_line_end = std::search(it_start,
		readBuf.end(), needle, needle + 2);

	if (it_line_end != readBuf.end())
	{
		switch (context.state)
		{
			case ParsingContext::startLine:
				parse_start_line(it_start, it_line_end, context);
				break;
			case ParsingContext::header:
				parse_header_line(it_start, it_line_end, context);
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
