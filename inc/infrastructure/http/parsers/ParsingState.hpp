/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParsingState.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 23:33:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:16:43 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPPARSINGSTATE_HPP
#define HTTPPARSINGSTATE_HPP

#include "infrastructure/http/Request.hpp"

namespace http {
struct ParsingState
{
	enum Step
	{
		start,
		requestLine,
		header,
		body,
		complete
	};

	ParsingState(void) : step(start), currenLineSize(0), currentHeaderCount(0), bodyBytesRead(0) {}

	Step		step;
	Request		request;
	std::size_t currenLineSize;
	std::size_t currentHeaderCount;
	std::size_t bodyBytesRead;
};
} // namespace http

#endif // HTTPPARSINGSTATE_HPP