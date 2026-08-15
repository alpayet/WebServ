/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 04:11:20 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:22:28 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/parsing/utils.hpp"
#include "infrastructure/server/application_protocol/parsing/constants.hpp"
#include <algorithm>

namespace {
int hex_to_dec(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}
} // namespace

namespace webserv {
namespace parse {

bool is_not_white_spaces(char c) { return (c != SP && c != HT); }

bool is_invalid_uri_char(unsigned char c) { return (c <= 32 || c == 127); }

char to_lower_safe(unsigned char c) { return (static_cast<char>(std::tolower(c))); }

void uri_decode(std::string &str)
{
	std::size_t writeIdx = 0;
	std::size_t len = str.length();

	for (std::size_t readIdx = 0; readIdx < len; ++readIdx)
	{
		if (str[readIdx] == '%' && readIdx + 2 < len)
		{
			int h1 = hex_to_dec(str[readIdx + 1]);
			int h2 = hex_to_dec(str[readIdx + 2]);

			if (h1 != -1 && h2 != -1)
			{
				str[writeIdx++] = static_cast<char>((h1 << 4) | h2);
				readIdx += 2;
				continue;
			}
		}

		if (str[readIdx] == '+')
			str[writeIdx++] = ' ';
		else
			str[writeIdx++] = str[readIdx];
	}
	str.resize(writeIdx);
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
} // namespace parse
} // namespace webserv