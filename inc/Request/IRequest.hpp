/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRequest.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 20:09:15 by alpayet           #+#    #+#             */
/*   Updated: 2026/04/21 20:17:26 by alpayet          ###   ########.fr       */
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

		virtual ParseState	parse(std::vector<char> const &readBuf) = 0;

};

#endif