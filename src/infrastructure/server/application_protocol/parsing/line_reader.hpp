/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_reader.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 03:37:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:22:13 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_LINE_READER_HPP
#define PARSE_LINE_READER_HPP

#include "infrastructure/server/application_protocol/parsing/constants.hpp"
#include <algorithm>
#include <vector>

namespace webserv {
namespace parse {
template <typename InputIterator> bool has_line_break(InputIterator it_start, InputIterator it_end)
{
	return ((std::find_first_of(it_start, it_end, CRLF, CRLF + sizeof(CRLF) - 1) != it_end));
}

std::vector<char>::const_iterator find_line_end(std::vector<char> &buf);

void consume_line(std::vector<char> &buf);
} // namespace parse
} // namespace webserv

#endif // PARSE_LINE_READER_HPP