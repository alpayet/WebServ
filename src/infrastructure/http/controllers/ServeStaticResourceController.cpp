/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourceController.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:30:26 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/14 21:47:02 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/controllers/ServeStaticResourceController.hpp"
#include "application/use_cases/serve_static_resource/ServeStaticResource.hpp"
#include "infrastructure/http/Request.hpp"
#include "infrastructure/http/Response.hpp"
#include "infrastructure/http/mappers/ServeStaticResourceDtoMapper.hpp"

namespace http {
ServeStaticResourceController::ServeStaticResourceController(
	app::useCase::ServeStaticResource &useCase
)
	: _useCase(useCase)
{}

void ServeStaticResourceController::operator()(
	Request const &request, Response &response, app::RoutePolicy const &routePolicy
)
{
	app::useCase::ServeStaticResource::Input dto =
		ServeStaticResourceDtoMapper::toDto(request, routePolicy);

	_useCase.execute(dto);
}
} // namespace http