/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestMapper.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 01:17:00 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/04 01:26:59 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTMAPPER_HPP
# define REQUESTMAPPER_HPP

# include "RequestDto.hpp"
# include "domain/entities/RequestEntity.hpp"

class RequestMapper
{
	public:
		static RequestEntity toDomain(RequestDto const &dto);

	private:
		RequestMapper(void) {}
};

#endif