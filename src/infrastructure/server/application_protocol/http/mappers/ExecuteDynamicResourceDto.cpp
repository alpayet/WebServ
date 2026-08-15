/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceDto.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:09:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:13:13 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/mappers/ExecuteDynamicResourceDto.hpp"
#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.hpp"
#include "infrastructure/server/application_protocol/http/request/Request.hpp"
#include "infrastructure/server/application_protocol/http/router/RoutePolicy.hpp"

namespace webserv {
namespace http {
namespace mapper {
app::useCase::ExecuteDynamicResource::Input ExecuteDynamicResourceDto::toDto(
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
} // namespace mapper
} // namespace http
} // namespace webserv