/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceDtoMapper.cpp                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:09:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/04 19:55:52 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/mappers/ExecuteDynamicResourceDtoMapper.hpp"
#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.hpp"
#include "infrastructure/server/application_protocol/http/request/Request.hpp"
#include "infrastructure/server/application_protocol/http/router/RoutePolicy.hpp"

namespace http {
app::useCase::ExecuteDynamicResource::Input ExecuteDynamicResourceDtoMapper::toDto(
	Request const							 &request,
	RoutePolicy const						 &routePolicy,
	std::string const						 &bodyPath,
	std::map<std::string, std::string> const &metaVariables
)
{
	return (app::useCase::ExecuteDynamicResource::Input(
		request.getTarget(), routePolicy.matchedRoute, routePolicy.rootPath, bodyPath, metaVariables
	));
}
} // namespace http