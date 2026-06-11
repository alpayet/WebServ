/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResourceDtoMapper.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:09:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/11 15:52:57 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/mappers/FindStaticResourceDtoMapper.hpp"
#include "application/use_cases/find_static_resource/FindStaticResource.hpp"
#include "infrastructure/http/Request.hpp"

namespace http
{
	useCase::FindStaticResource::Input
	FindStaticResourceDtoMapper::toDto(Request const &request, RoutePolicy const &routePolicy)
	{
		(useCase::FindStaticResource::Input){.id = request.target, .routePolicy = routePolicy};
	}
} // namespace http