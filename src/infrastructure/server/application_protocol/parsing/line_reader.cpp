/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_reader.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 03:41:46 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:22:06 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/parsing/line_reader.hpp"
#include "infrastructure/server/application_protocol/parsing/constants.hpp"
#include <algorithm>

namespace webserv {
namespace parse {
std::vector<char>::const_iterator find_line_end(std::vector<char> &buf)
{
	std::vector<char>::const_iterator it = std::find(buf.begin(), buf.end(), LF);

	if (it == buf.end())
		return (it);

	if (it != buf.begin() && *(it - 1) == CR)
		return (it - 1);

	return (it);
}

void consume_line(std::vector<char> &buf)
{
	std::vector<char>::iterator it = std::find(buf.begin(), buf.end(), LF);

	buf.erase(buf.begin(), it + 1);
}
} // namespace parse
} // namespace webserv
