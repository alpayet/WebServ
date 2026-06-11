/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResourceController.cpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:30:26 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/11 15:55:10 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/controllers/DeleteStaticResourceController.hpp"
#include "application/use_cases/delete_static_resource/DeleteStaticResource.hpp"
#include "infrastructure/http/Request.hpp"
#include "infrastructure/http/Response.hpp"
#include "infrastructure/http/mappers/DeleteStaticResourceDtoMapper.hpp"

namespace http
{
	DeleteStaticResourceController::DeleteStaticResourceController(
		useCase::DeleteStaticResource &useCase
	)
		: _useCase(useCase)
	{
	}

	void DeleteStaticResourceController::operator()(
		Request const &request, Response &response, RoutePolicy const &routePolicy
	)
	{
		useCase::DeleteStaticResource::Input dto =
			DeleteStaticResourceDtoMapper::toDto(request, routePolicy);

		_useCase.execute(dto);
	}
} // namespace http