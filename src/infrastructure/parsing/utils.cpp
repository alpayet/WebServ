/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 04:11:20 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/08 04:46:41 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/parsing/utils.hpp"
#include "infrastructure/parsing/constants.hpp"
#include <algorithm>

namespace parse {
template <typename InputIterator>
InputIterator find_white_spaces(InputIterator it_start, InputIterator it_end)
{
	return (
		std::find_first_of(it_start, it_end, WHITE_SPACES, WHITE_SPACES + sizeof(WHITE_SPACES) - 1)
	);
}

bool is_not_white_spaces(char c) { return (c != SP && c != HT); }

template <typename InputIterator>
bool is_valid_uri_syntax(InputIterator it_start, InputIterator it_end)
{
	if (it_start == it_end)
		return (false);
	if (std::find_if(it_start, it_end, is_invalid_uri_char) != it_end)
		return (false);
	return (true);
}

bool is_invalid_uri_char(unsigned char c) { return (c <= 32 || c == 127); }

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