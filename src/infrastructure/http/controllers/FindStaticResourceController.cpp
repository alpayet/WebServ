/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResourceController.cpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:30:26 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/11 15:54:13 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/controllers/FindStaticResourceController.hpp"
#include "application/use_cases/find_static_resource/FindStaticResource.hpp"
#include "infrastructure/http/Request.hpp"
#include "infrastructure/http/Response.hpp"
#include "infrastructure/http/mappers/FindStaticResourceDtoMapper.hpp"

struct RoutePolicy;
namespace http
{
	FindStaticResourceController::FindStaticResourceController(useCase::FindStaticResource &useCase)
		: _useCase(useCase)
	{
	}

	void FindStaticResourceController::operator()(
		Request const &request, Response &response, RoutePolicy const &routePolicy
	)
	{
		useCase::FindStaticResource::Input dto =
			FindStaticResourceDtoMapper::toDto(request, routePolicy);

		_useCase.execute(dto);
	}
} // namespace http