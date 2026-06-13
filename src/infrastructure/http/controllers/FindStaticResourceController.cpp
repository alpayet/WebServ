/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResourceController.cpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:30:26 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:27:17 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/controllers/FindStaticResourceController.hpp"
#include "application/use_cases/find_static_resource/FindStaticResource.hpp"
#include "infrastructure/http/Request.hpp"
#include "infrastructure/http/Response.hpp"
#include "infrastructure/http/mappers/FindStaticResourceDtoMapper.hpp"

namespace http {
FindStaticResourceController::FindStaticResourceController(
	app::useCase::FindStaticResource &useCase
)
	: _useCase(useCase)
{}

void FindStaticResourceController::operator()(
	Request const &request, Response &response, app::RoutePolicy const &routePolicy
)
{
	app::useCase::FindStaticResource::Input dto =
		FindStaticResourceDtoMapper::toDto(request, routePolicy);

	_useCase.execute(dto);
}
} // namespace http