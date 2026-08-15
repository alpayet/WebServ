/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResourceDto.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:09:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:12:55 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/mappers/DeleteStaticResourceDto.hpp"
#include "application/use_cases/delete_static_resource/DeleteStaticResource.hpp"
#include "infrastructure/server/application_protocol/http/request/Request.hpp"
#include "infrastructure/server/application_protocol/http/router/RoutePolicy.hpp"

namespace webserv {
namespace http {
namespace mapper {

app::useCase::DeleteStaticResource::Input
DeleteStaticResourceDto::toDto(Request const &request, RoutePolicy const &routePolicy)
{
	return (app::useCase::DeleteStaticResource::Input(
		request.getTarget(), routePolicy.matchedRoute, routePolicy.rootPath
	));
}
} // namespace mapper
} // namespace http
} // namespace webserv