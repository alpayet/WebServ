/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParsingState.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 23:33:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/24 23:07:57 by alpayet          ###   ########.fr       */
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

		std::size_t pos;
		Step		step;
		Request		request;
	};
} // namespace http

#endif // HTTPPARSINGSTATE_HPP