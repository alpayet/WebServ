/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 02:29:14 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/04 04:36:58 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgi/Parser.hpp"

namespace cgi {
Parser::State::State(void) : step(header), response() {}

void Parser::State::reset(void)
{
	step = header;
	response.reset();
}

Parser::Step cgi::Parser::parse(std::vector<char> &inputBuf, cgi::Parser::State &state)
{
	switch (state.step)
	{
		case header:
			/* code */
			break;
		case body:
			/* code */
			break;

		default:
			break;
	}
}
} // namespace cgi
