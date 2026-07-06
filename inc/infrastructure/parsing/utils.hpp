/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 03:33:19 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/06 23:29:51 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSINGUTILS_HPP
#define PARSINGUTILS_HPP

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

std::vector<char>::const_iterator find_white_spaces(
	std::vector<char>::const_iterator it_start, std::vector<char>::const_iterator it_end
);
std::vector<char>::const_iterator find_line_end(std::vector<char> &buf);

bool has_line_break(
	std::vector<char>::const_iterator it_start, std::vector<char>::const_iterator it_end
);

void consume_line(std::vector<char> &buf);

bool is_valid_key_syntax(
	std::vector<char>::const_iterator it_start, std::vector<char>::const_iterator it_end
);
bool is_valid_value_syntax(
	std::vector<char>::const_iterator it_start, std::vector<char>::const_iterator it_end
);

bool is_invalid_key_char(unsigned char c);
bool is_invalid_value_char(unsigned char c);

bool is_not_white_spaces(char c);
char to_lower_safe(unsigned char c);
void trim(std::string &str, char const *to_trim);
} // namespace parse

#endif // PARSINGUTILS_HPP