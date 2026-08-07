/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResourceDtoMapper.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:09:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/04 19:55:52 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/mappers/DeleteStaticResourceDtoMapper.hpp"
#include "application/use_cases/delete_static_resource/DeleteStaticResource.hpp"
#include "infrastructure/server/application_protocol/http/request/Request.hpp"
#include "infrastructure/server/application_protocol/http/router/RoutePolicy.hpp"

namespace http {
app::useCase::DeleteStaticResource::Input
DeleteStaticResourceDtoMapper::toDto(Request const &request, RoutePolicy const &routePolicy)
{
	return (app::useCase::DeleteStaticResource::Input(
		request.getTarget(), routePolicy.matchedRoute, routePolicy.rootPath
	));
}
} // namespace http