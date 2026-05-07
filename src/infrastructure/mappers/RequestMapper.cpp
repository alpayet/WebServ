/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestMapper.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 01:33:19 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/07 19:45:49 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/mappers/RequestMapper.hpp"
#include "domain/builders/RequestBuilder.hpp"

RequestEntity	RequestMapper::toDomain(HttpRequestDto const &dto)
{
	return (RequestBuilder().withTarget(dto.target)
							.withProtocol(dto.protocol)
							.withHeaders(dto.headers)
							.build());
}
