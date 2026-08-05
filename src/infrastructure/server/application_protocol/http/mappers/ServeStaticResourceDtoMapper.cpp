/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourceDtoMapper.cpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:09:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/04 19:55:52 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/mappers/ServeStaticResourceDtoMapper.hpp"
#include "application/use_cases/serve_static_resource/ServeStaticResource.hpp"
#include "infrastructure/server/application_protocol/http/request/Request.hpp"
#include "infrastructure/server/application_protocol/http/router/RoutePolicy.hpp"

namespace http {
app::useCase::ServeStaticResource::Input
ServeStaticResourceDtoMapper::toDto(Request const &request, RoutePolicy const &routePolicy)
{
	return (app::useCase::ServeStaticResource::Input(
		request.getTarget(), routePolicy.matchedRoute, routePolicy.rootPath,
		routePolicy.isListingEnabled, routePolicy.indexesId
	));
}
} // namespace http