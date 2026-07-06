/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 04:11:20 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/06 23:29:51 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/parsing/utils.hpp"
#include "infrastructure/parsing/constants.hpp"
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
	if (has_line_break(it_start, it_line_end))
		return (ParseHeaderLine::lineBreakInvalid);

	std::vector<char>::const_iterator it_colon;
	it_colon = std::find(it_start, it_line_end, COLON);
	if (it_colon == it_line_end)
		return (ParseHeaderLine::malformed);

	if (!is_valid_key_syntax(it_start, it_colon))
		return (ParseHeaderLine::keyInvalid);

	out_key.assign(it_start, it_colon);

	std::transform(out_key.begin(), out_key.end(), out_key.begin(), to_lower_safe);

	if (!is_valid_value_syntax(it_colon + 1, it_line_end))
		return (ParseHeaderLine::valueInvalid);

	out_value.assign(it_colon + 1, it_line_end);
	trim(out_value, WHITE_SPACES);
	return (ParseHeaderLine::success);
}

ParseContentLength::Result parse_content_length(
	std::map<std::string, std::string> const &headers,
	std::size_t								  max_body_size,
	std::size_t								 &out_content_length
)
{
	std::map<std::string, std::string>::const_iterator it =
		headers.find(header::LOWER_CONTENT_LENGTH);

	if (it == headers.end())
		return (ParseContentLength::contentLengthMissing);

	std::string content_length = it->second;
	if (content_length.empty())
		return (ParseContentLength::contentLengthInvalid);

	char *endptr = NULL;
	errno = 0;
	unsigned long long val = std::strtoull(content_length.c_str(), &endptr, 10);

	if (errno == ERANGE || *endptr != '\0' || content_length[0] == '-')
		return (ParseContentLength::contentLengthInvalid);
	if (val > max_body_size)
		return (ParseContentLength::bodyTooLarge);
	out_content_length = static_cast<size_t>(val);
	return (ParseContentLength::success);
}

std::vector<char>::const_iterator find_white_spaces(
	std::vector<char>::const_iterator it_start, std::vector<char>::const_iterator it_end
)
{
	return (
		std::find_first_of(it_start, it_end, WHITE_SPACES, WHITE_SPACES + sizeof(WHITE_SPACES) - 1)
	);
}

std::vector<char>::const_iterator find_line_end(std::vector<char> &buf)
{
	std::vector<char>::const_iterator it = std::find(buf.begin(), buf.end(), LF);

	if (it == buf.end())
		return (it);

	if (it != buf.begin() && *(it - 1) == CR)
		return (it - 1);

	return (it);
}

bool has_line_break(
	std::vector<char>::const_iterator it_start, std::vector<char>::const_iterator it_end
)
{
	return ((std::find_first_of(it_start, it_end, CRLF, CRLF + sizeof(CRLF) - 1) != it_end));
}

void consume_line(std::vector<char> &buf)
{
	std::vector<char>::iterator it = std::find(buf.begin(), buf.end(), LF);

	buf.erase(buf.begin(), it + 1);
}

bool is_valid_key_syntax(
	std::vector<char>::const_iterator it_start, std::vector<char>::const_iterator it_end
)
{
	if (it_start == it_end)
		return (false);
	if (std::find_if(it_start, it_end, is_invalid_key_char) != it_end)
		return (false);
	return (true);
}

bool is_valid_value_syntax(
	std::vector<char>::const_iterator it_start, std::vector<char>::const_iterator it_end
)
{
	if (it_start == it_end)
		return (false);
	if (std::find_if(it_start, it_end, is_invalid_value_char) != it_end)
		return (false);
	return (true);
}

bool is_invalid_key_char(unsigned char c)
{
	static std::string const specials_authorized = "?!#$%&'*+-.^_`|~";

	return (!(std::isalnum(c) || specials_authorized.find(c) != std::string::npos));
}

bool is_invalid_value_char(unsigned char c) { return ((c < 32 && c != HT) || c == 127); }

bool is_not_white_spaces(char c) { return (c != SP && c != HT); }

char to_lower_safe(unsigned char c) { return (static_cast<char>(std::tolower(c))); }

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
} // namespace parse