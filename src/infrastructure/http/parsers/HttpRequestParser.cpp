/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequestParser.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:40:42 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/18 20:29:08 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http/message/IRequest.hpp"
#include "infrastructure/http/parsers/RequestParser.hpp"
#include "infrastructure/http/Methods.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"
#include <algorithm>

namespace
{
	void	parse_start_line(std::vector<char>::const_iterator it_start,
		std::vector<char>::const_iterator it_line_end, Http::ParsingState &state)
	{
		std::vector<char>::const_iterator	it_first_space;
		std::vector<char>::const_iterator	it_second_space;

		while (it_start[0] == '\r' && it_start[1] == '\n')
			it_start += 2;

		ensure_no_line_break(it_start, it_line_end);

		if (std::count(it_start, it_line_end, ' ') != 2)
			throw Http::Exception(Http::Exception::malformedStartLine);
		it_first_space = std::find(it_start, it_line_end, ' ');
		it_second_space = std::find(it_first_space + 1, it_line_end, ' ');

		std::string	method(it_start, it_first_space);
		if (!Http::isMethodSupported(method))
			throw Http::Exception(Http::Exception::invalidMethod);
		state.request.method = method;

		if (!is_valid_target_syntax(it_first_space + 1, it_second_space))
			throw Http::Exception(Http::Exception::invalidTarget);
		std::string	target(it_first_space + 1, it_second_space);
		state.request.target = target;

		std::string	protocol(it_second_space + 1, it_line_end);
		state.request.protocol = protocol;

		state.step = Http::ParsingState::header;
	}

	void	parse_header_line(std::vector<char>::const_iterator it_start,
		std::vector<char>::const_iterator it_line_end, Http::ParsingState &state)
	{
		if (it_start == it_line_end)
		{
			state.step = Http::ParsingState::body;
			return ;
		}

		ensure_no_line_break(it_start, it_line_end - 1);

		std::vector<char>::const_iterator	it_colon;
		it_colon = std::find(it_start, it_line_end, ':');

		if (!is_valid_key_syntax(it_start, it_colon))
			throw Http::Exception(Http::Exception::invalidHeaderKey);
		std::string	key(it_start, it_colon);
		std::transform(key.begin(), key.end(), key.begin(), to_lower_safe);

		if (!is_valid_value_syntax(it_colon + 1, it_line_end))
			throw Http::Exception(Http::Exception::invalidHeaderValue);
		std::string	value(it_colon + 1, it_line_end);
		trim(value, " \t");

		state.request.headers[key] = value;
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

	void ensure_no_line_break(std::vector<char>::const_iterator it_start,
		std::vector<char>::const_iterator it_end)
	{
		static char const line_breakers[] = {'\r', '\n'};
		if (std::find_first_of(it_start, it_end,
			line_breakers, line_breakers + 2) != it_end)
			throw Http::Exception(Http::Exception::invalidLineBreak);
	}

	bool	is_valid_target_syntax(
		std::vector<char>::const_iterator it_start, std::vector<char>::const_iterator it_end)
	{
		if (it_start == it_end)
			return (false);
		if (*it_start != '/')
			return (false);
		if (std::find(it_start, it_end, is_invalid_target_char) != it_end)
			return (false);
	}

	bool	is_invalid_target_char(unsigned char c)
	{
		return (!(std::isprint(c) || c >= 128));
	}

	bool	is_valid_key_syntax(
		std::vector<char>::const_iterator it_start, std::vector<char>::const_iterator it_end)
	{
		if (it_start == it_end)
			return (false);
		if (std::find(it_start, it_end, is_invalid_key_char) != it_end)
			return (false);
	}

	bool	is_invalid_key_char(unsigned char c)
	{
		static const std::string	specials_authorized = "!#$%&'*+-.^_`|~";

		return (!(std::isalnum(c) ||
			specials_authorized.find(c) != std::string::npos));
	}

	bool	is_valid_value_syntax(
		std::vector<char>::const_iterator it_start, std::vector<char>::const_iterator it_end)
	{
		if (it_start == it_end)
			return (false);
		if (std::find(it_start, it_end, is_invalid_value_char) != it_end)
			return (false);
	}

	bool is_invalid_value_char(unsigned char c)
	{
		return (!(std::isprint(c) || c == '\t' || c >= 128));
	}
}

Http::ParsingState::Step Http::RequestParser::parse(
	std::vector<char> const &readBuf, Http::ParsingState &context)
{
	std::vector<char>::const_iterator	it_start = readBuf.begin() + context.pos;
	static char const					needle[] = {'\r', '\n'};
	std::vector<char>::const_iterator	it_line_end = std::search(it_start,
		readBuf.end(), needle, needle + 2);

	if (it_line_end != readBuf.end())
	{
		switch (context.step)
		{
			case Http::ParsingState::startLine:
				parse_start_line(it_start, it_line_end, context);
				break;
			case Http::ParsingState::header:
				parse_header_line(it_start, it_line_end, context);
				break;
			default:
				break;
		}
		// if (context.step == ParsingContext::Complete)
		// {
		// 	RequestEntity	request_entity = RequestMapper::toDomain(this->_requestDto);
		// 	this->_requestInputPort->handle(request_entity);
		// }
		context.pos += std::distance(it_start, it_line_end) + 2;
	}
	return (context.step);
}
