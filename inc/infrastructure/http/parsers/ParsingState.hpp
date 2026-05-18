/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParsingState.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 23:33:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/18 19:49:46 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPPARSINGSTATE_HPP
# define HTTPPARSINGSTATE_HPP

# include "infrastructure/http/Request.hpp"

namespace Http
{
	struct ParsingState
	{
		enum Step
		{
			startLine,
			header,
			body,
			complete
		};

		std::size_t		pos;
		Step			step;
		Http::Request	request;
	};
}

#endif