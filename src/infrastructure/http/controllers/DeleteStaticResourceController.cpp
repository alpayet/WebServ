/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResourceController.cpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:30:26 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/16 23:29:22 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/controllers/DeleteStaticResourceController.hpp"
#include "application/use_cases/delete_static_resource/DeleteStaticResource.hpp"
#include "infrastructure/http/mappers/DeleteStaticResourceDtoMapper.hpp"
#include "infrastructure/http/messages/Request.hpp"
#include "infrastructure/http/messages/Response.hpp"

namespace http {
DeleteStaticResourceController::DeleteStaticResourceController(
	app::useCase::DeleteStaticResource &useCase
)
	: _useCase(useCase)
{}

void DeleteStaticResourceController::operator()(
	Request const &request, Response &response, RoutePolicy const &routePolicy
)
{
	app::useCase::DeleteStaticResource::Input const &dto =
		DeleteStaticResourceDtoMapper::toDto(request, routePolicy);

	_useCase.execute(dto);
}
} // namespace http