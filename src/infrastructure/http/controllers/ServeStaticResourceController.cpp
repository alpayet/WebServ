/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourceController.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:30:26 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/16 23:28:53 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/controllers/ServeStaticResourceController.hpp"
#include "application/use_cases/serve_static_resource/ServeStaticResource.hpp"
#include "infrastructure/http/mappers/ServeStaticResourceDtoMapper.hpp"
#include "infrastructure/http/messages/Request.hpp"
#include "infrastructure/http/messages/Response.hpp"
#include "infrastructure/http/presenters/ServeStaticResourcePresenter.hpp"

namespace http {
ServeStaticResourceController::ServeStaticResourceController(
	app::useCase::ServeStaticResource &useCase
)
	: _useCase(useCase)
{}

void ServeStaticResourceController::operator()(
	Request const &request, Response &response, RoutePolicy const &routePolicy
)
{
	app::useCase::ServeStaticResource::Input const &dto =
		ServeStaticResourceDtoMapper::toDto(request, routePolicy);

	ServeStaticResourcePresenter presenter;
	_useCase.execute(dto, presenter);
}
} // namespace http