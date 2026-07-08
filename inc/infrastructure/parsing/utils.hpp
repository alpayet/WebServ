/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 03:33:19 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/08 04:46:58 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSINGUTILS_HPP
#define PARSINGUTILS_HPP

#include <string>

namespace parse {

template <typename InputIterator>
InputIterator find_white_spaces(InputIterator it_start, InputIterator it_end);

bool is_not_white_spaces(char c);

template <typename InputIterator>
bool is_valid_uri_syntax(InputIterator it_start, InputIterator it_end);

bool is_invalid_uri_char(unsigned char c);
char to_lower_safe(unsigned char c);
void trim(std::string &str, char const *to_trim);
} // namespace parse

#endif // PARSINGUTILS_HPP