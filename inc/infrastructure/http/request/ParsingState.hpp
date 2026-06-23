/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParsingState.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 23:33:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/23 03:32:29 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUESTPARSINGSTATE_HPP
#define HTTPREQUESTPARSINGSTATE_HPP

#include "Parser.hpp"
#include "Request.hpp"

namespace http {
namespace request {

struct ParsingState
{
	ParsingState(void)
		: step(Parser::start), currenLineSize(0), currentHeaderCount(0), bodyBytesRead(0)
	{}

	Parser::Step step;
	Request		 request;
	std::size_t	 currenLineSize;
	std::size_t	 currentHeaderCount;
	std::size_t	 bodyBytesRead;
};
} // namespace request
} // namespace http

#endif // HTTPREQUESTPARSINGSTATE_HPP