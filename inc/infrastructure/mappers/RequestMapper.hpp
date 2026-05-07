/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestMapper.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 01:17:00 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/07 19:49:41 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTMAPPER_HPP
# define REQUESTMAPPER_HPP

# include "infrastructure/dtos/HttpRequestDto.hpp"
# include "domain/entities/RequestEntity.hpp"

class RequestMapper
{
	public:
		static RequestEntity toDomain(HttpRequestDto const &dto);

	private:
		RequestMapper(void) {}
};

#endif