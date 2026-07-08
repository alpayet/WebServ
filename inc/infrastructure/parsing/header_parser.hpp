/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_parser.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 03:37:10 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/08 03:40:03 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HEADER_PARSER_HPP
#define PARSE_HEADER_PARSER_HPP

#include <map>
#include <string>
#include <vector>

namespace parse {
struct ParseHeaderLine
{
	enum Result
	{
		success,
		lineBreakInvalid,
		malformed,
		keyInvalid,
		valueInvalid
	};
};

struct ParseContentLength
{
	enum Result
	{
		success,
		contentLengthMissing,
		contentLengthInvalid,
		bodyTooLarge
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

template <typename InputIterator>
bool is_valid_key_syntax(InputIterator it_start, InputIterator it_end);
template <typename InputIterator>
bool is_valid_value_syntax(InputIterator it_start, InputIterator it_end);

bool is_invalid_key_char(unsigned char c);
bool is_invalid_value_char(unsigned char c);
} // namespace parse

#endif // PARSE_HEADER_PARSER_HPP