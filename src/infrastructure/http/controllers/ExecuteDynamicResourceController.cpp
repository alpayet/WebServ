/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceController.cpp               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:30:26 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:23:51 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/controllers/ExecuteDynamicResourceController.hpp"
#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.hpp"
#include "infrastructure/http/Request.hpp"
#include "infrastructure/http/Response.hpp"
#include "infrastructure/http/mappers/ExecuteDynamicResourceDtoMapper.hpp"

namespace http {
ExecuteDynamicResourceController::ExecuteDynamicResourceController(
	app::useCase::ExecuteDynamicResource &useCase
)
	: _useCase(useCase)
{}

void ExecuteDynamicResourceController::operator()(
	Request const &request, Response &response, app::RoutePolicy const &routePolicy
)
{
	app::useCase::ExecuteDynamicResource::Input dto =
		ExecuteDynamicResourceDtoMapper::toDto(request, routePolicy);

	_useCase.execute(dto);
}
} // namespace http