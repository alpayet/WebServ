/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_reader.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 03:37:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/08 03:40:33 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_LINE_READER_HPP
#define PARSE_LINE_READER_HPP

#include <vector>

namespace parse {
template <typename InputIterator> bool has_line_break(InputIterator it_start, InputIterator it_end);

std::vector<char>::const_iterator find_line_end(std::vector<char> &buf);

void consume_line(std::vector<char> &buf);
} // namespace parse

#endif // PARSE_LINE_READER_HPP