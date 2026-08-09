/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourceDto.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:09:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/09 22:22:40 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/mappers/ServeStaticResourceDto.hpp"
#include "application/use_cases/serve_static_resource/ServeStaticResource.hpp"
#include "infrastructure/server/application_protocol/http/request/Request.hpp"
#include "infrastructure/server/application_protocol/http/router/RoutePolicy.hpp"

namespace http {
namespace mapper {
app::useCase::ServeStaticResource::Input
ServeStaticResourceDto::toDto(Request const &request, RoutePolicy const &routePolicy)
{
	return (app::useCase::ServeStaticResource::Input(
		request.getTarget(), routePolicy.matchedRoute, routePolicy.rootPath,
		routePolicy.isListingEnabled, routePolicy.indexesId
	));
}
} // namespace mapper

} // namespace http