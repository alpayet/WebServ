/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParsingContext.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 23:33:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/07 19:48:50 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSINGCONTEXT_HPP
# define PARSINGCONTEXT_HPP

# include "infrastructure/dtos/HttpRequestDto.hpp"

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
	HttpRequestDto	requestDto;
};

#endif