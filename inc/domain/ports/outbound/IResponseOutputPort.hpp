/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IResponseOutputPort.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 19:12:46 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/04 18:07:47 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRESPONSEOUTPUTPORT_HPP
# define IRESPONSEOUTPUTPORT_HPP

# include "entities/ResponseEntity.hpp"

class IResponseOutputPort
{
	public:
		virtual ~IResponseOutputPort(void) {}

		virtual void	present(ResponseEntity const &responseEntity) = 0;
};

#endif