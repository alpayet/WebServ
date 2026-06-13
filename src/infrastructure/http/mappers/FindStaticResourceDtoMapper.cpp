/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResourceDtoMapper.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:09:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/13 01:44:33 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/mappers/FindStaticResourceDtoMapper.hpp"
#include "application/use_cases/find_static_resource/FindStaticResource.hpp"
#include "infrastructure/http/Request.hpp"

namespace http {
app::useCase::FindStaticResource::Input
FindStaticResourceDtoMapper::toDto(Request const &request, app::RoutePolicy const &routePolicy)
{
	return (
		(app::useCase::FindStaticResource::Input){.id = request.target, .routePolicy = routePolicy}
	);
}
} // namespace http