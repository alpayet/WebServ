/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestMapper.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 01:33:19 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/04 17:12:31 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/adapters/inbound/RequestMapper.hpp"
#include "domain/services/RequestBuilder.hpp"

RequestEntity	RequestMapper::toDomain(RequestDto const &dto)
{
	return (RequestBuilder().withTarget(dto.target)
							.withProtocol(dto.protocol)
							.withHeaders(dto.headers)
							.build());
}
