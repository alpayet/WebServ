/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IResponseOutputPort.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 19:12:46 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/03 19:26:01 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRESPONSEOUTPUTPORT_HPP
# define IRESPONSEOUTPUTPORT_HPP

# include "shared/ResponseDto.hpp"

class IResponseOutputPort
{
	public:
		virtual ~IResponseOutputPort(void) {}

		virtual void	present(ResponseDto const &responseDto) = 0;
};

#endif