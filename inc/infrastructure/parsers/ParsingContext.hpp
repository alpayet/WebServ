/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParsingContext.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 23:33:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/05 20:06:57 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSINGCONTEXT_HPP
# define PARSINGCONTEXT_HPP

# include "infrastructure/dtos/RequestDto.hpp"

struct ParsingContext
{
	enum ParseState
	{
		startLine,
		header,
		body,
		complete
	};

	std::size_t	pos;
	ParseState	state;
	RequestDto	requestDto;
};

#endif