/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRequest.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 20:09:15 by alpayet           #+#    #+#             */
/*   Updated: 2026/04/19 22:52:18 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IREQUEST_HPP
# define IREQUEST_HPP

class IRequest
{
	public:
		enum ParseState
		{
			ParseState_Header,
			ParseState_Body,
			ParseState_Complete
		};

	public:
		virtual ~IRequest(void) {}

		virtual ParseState	parse() = 0;

};

#endif