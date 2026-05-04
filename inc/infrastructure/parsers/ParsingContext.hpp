/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParsingContext.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 23:33:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/04 23:52:24 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSINGCONTEXT_HPP
# define PARSINGCONTEXT_HPP

# include "infrastructure/dtos/RequestDto.hpp"

struct ParsingContext
{
	enum ParseState
	{
		StartLine,
		Header,
		Body,
		Complete
	};

	std::size_t	pos;
	ParseState	state;
	RequestDto	requestDto;
};

#endif