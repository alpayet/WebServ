/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRequestInputPort.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 17:05:33 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/03 21:32:55 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IREQUESTINPUTPORT_HPP
# define IREQUESTINPUTPORT_HPP

# include "shared/RequestDto.hpp"

class IRequestInputPort
{
	public:
		virtual ~IRequestInputPort(void) {}

		virtual void	handle(RequestEntity const &requestDto) = 0;
};

#endif