/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_parser.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 03:37:10 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:21:44 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HEADER_PARSER_HPP
#define PARSE_HEADER_PARSER_HPP

#include <algorithm>
#include <map>
#include <string>
#include <vector>

namespace webserv {
namespace parse {
struct ParseHeaderLine
{
	enum Result
	{
		SUCCESS,
		LINE_BREAK_INVALID,
		MALFORMED,
		KEY_INVALID,
		VALUE_INVALID
	};
};

struct ParseContentLength
{
	enum Result
	{
		SUCCESS,
		NO_CONTENT_LENGTH,
		CONTENT_LENGTH_INVALID,
		BODY_TOO_LARGE
	};
};

ParseHeaderLine::Result parse_header_line(
	std::vector<char>::const_iterator it_start,
	std::vector<char>::const_iterator it_line_end,
	std::string						 &out_key,
	std::string						 &out_value
);

ParseContentLength::Result parse_content_length(
	std::map<std::string, std::string> const &headers,
	std::size_t								  max_body_size,
	std::size_t								 &out_content_length
);

bool is_invalid_key_char(unsigned char c);
bool is_invalid_value_char(unsigned char c);

template <typename InputIterator>
bool is_valid_key_syntax(InputIterator it_start, InputIterator it_end)
{
	if (it_start == it_end)
		return (false);
	if (std::find_if(it_start, it_end, is_invalid_key_char) != it_end)
		return (false);
	return (true);
}

template <typename InputIterator>
bool is_valid_value_syntax(InputIterator it_start, InputIterator it_end)
{
	if (it_start == it_end)
		return (false);
	if (std::find_if(it_start, it_end, is_invalid_value_char) != it_end)
		return (false);
	return (true);
}

} // namespace parse
} // namespace webserv

#endif // PARSE_HEADER_PARSER_HPP
