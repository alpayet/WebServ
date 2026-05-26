/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParsingState.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 23:33:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/26 18:23:38 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPPARSINGSTATE_HPP
#define HTTPPARSINGSTATE_HPP

#include "infrastructure/http/Request.hpp"

namespace http
{
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

		Step		step;
		Request		request;
		std::size_t bodyBytesRead;
	};
} // namespace http

#endif // HTTPPARSINGSTATE_HPP