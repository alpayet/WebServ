/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 03:33:19 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:22:36 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSINGUTILS_HPP
#define PARSINGUTILS_HPP

#include "infrastructure/server/application_protocol/parsing/constants.hpp"
#include <algorithm>
#include <string>

namespace webserv {
namespace parse {
template <typename InputIterator>
InputIterator find_white_spaces(InputIterator it_start, InputIterator it_end)
{
	return (
		std::find_first_of(it_start, it_end, WHITE_SPACES, WHITE_SPACES + sizeof(WHITE_SPACES) - 1)
	);
}

bool is_invalid_uri_char(unsigned char c);

template <typename InputIterator>
bool is_valid_uri_syntax(InputIterator it_start, InputIterator it_end)
{
	if (it_start == it_end)
		return (false);
	if (std::find_if(it_start, it_end, is_invalid_uri_char) != it_end)
		return (false);
	return (true);
}

bool is_not_white_spaces(char c);
char to_lower_safe(unsigned char c);
void uri_decode(std::string &str);
void trim(std::string &str, char const *to_trim);
} // namespace parse
} // namespace webserv

#endif // PARSINGUTILS_HPP