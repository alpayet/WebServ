/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourceDtoMapper.cpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:09:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/04 03:08:18 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/mappers/ServeStaticResourceDtoMapper.hpp"
#include "application/use_cases/serve_static_resource/ServeStaticResource.hpp"
#include "infrastructure/http/request/Request.hpp"
#include "infrastructure/http/router/RoutePolicy.hpp"

namespace http {
app::useCase::ServeStaticResource::Input
ServeStaticResourceDtoMapper::toDto(Request const &request, RoutePolicy const &routePolicy)
{
	return (app::useCase::ServeStaticResource::Input(
		request.startLine.target, routePolicy.matchedRoute, routePolicy.rootPath,
		routePolicy.isListingEnabled, routePolicy.indexesId
	));
}
} // namespace http