/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_parser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 03:41:24 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/04 20:03:54 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/parsing/header_parser.hpp"
#include "infrastructure/constants.hpp"
#include "infrastructure/parsing/line_reader.hpp"
#include "infrastructure/parsing/utils.hpp"
#include <algorithm>
#include <cerrno>

namespace parse {
ParseHeaderLine::Result parse_header_line(
	std::vector<char>::const_iterator it_start,
	std::vector<char>::const_iterator it_line_end,
	std::string						 &out_key,
	std::string						 &out_value
)
{
	if (parse::has_line_break(it_start, it_line_end))
		return (ParseHeaderLine::LINE_BREAK_INVALID);

	std::vector<char>::const_iterator it_colon;
	it_colon = std::find(it_start, it_line_end, COLON);
	if (it_colon == it_line_end)
		return (ParseHeaderLine::MALFORMED);

	if (!is_valid_key_syntax(it_start, it_colon))
		return (ParseHeaderLine::KEY_INVALID);

	out_key.assign(it_start, it_colon);

	std::transform(out_key.begin(), out_key.end(), out_key.begin(), parse::to_lower_safe);

	if (!is_valid_value_syntax(it_colon + 1, it_line_end))
		return (ParseHeaderLine::VALUE_INVALID);

	out_value.assign(it_colon + 1, it_line_end);
	trim(out_value, WHITE_SPACES);
	return (ParseHeaderLine::SUCCESS);
}

ParseContentLength::Result parse_content_length(
	std::map<std::string, std::string> const &headers,
	std::size_t								  max_body_size,
	std::size_t								 &out_content_length
)
{
	std::map<std::string, std::string>::const_iterator it = headers.find(headers::CONTENT_LENGTH);

	if (it == headers.end())
		return (ParseContentLength::NO_CONTENT_LENGTH);

	std::string content_length = it->second;
	if (content_length.empty())
		return (ParseContentLength::CONTENT_LENGTH_INVALID);

	char *endptr = NULL;
	errno = 0;
	unsigned long long val = std::strtoull(content_length.c_str(), &endptr, 10);

	if (errno == ERANGE || *endptr != '\0' || content_length[0] == '-')
		return (ParseContentLength::CONTENT_LENGTH_INVALID);
	if (val > max_body_size)
		return (ParseContentLength::BODY_TOO_LARGE);
	out_content_length = static_cast<size_t>(val);
	return (ParseContentLength::SUCCESS);
}

bool is_invalid_key_char(unsigned char c)
{
	static std::string const specials_authorized = "?!#$%&'*+-.^_`|~";

	return (!(std::isalnum(c) || specials_authorized.find(c) != std::string::npos));
}

bool is_invalid_value_char(unsigned char c) { return ((c < 32 && c != HT) || c == 127); }

} // namespace parse
