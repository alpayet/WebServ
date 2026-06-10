/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResourceController.cpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:30:26 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/10 19:45:18 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/controllers/FindStaticResourceController.hpp"
#include "application/use_cases/find_static_resource/FindStaticResource.hpp"
#include "application/use_cases/find_static_resource/FindStaticResourceInput.hpp"
#include "application/use_cases/find_static_resource/FindStaticResourceOutput.hpp"
#include "infrastructure/http/Request.hpp"
#include "infrastructure/http/Response.hpp"
#include "infrastructure/http/mappers/FindStaticResourceDtoMapper.hpp"

namespace http
{
	FindStaticResourceController::FindStaticResourceController(useCase::FindStaticResource &useCase)
		: _useCase(useCase)
	{
	}

	void FindStaticResourceController::operator()(Request const &request, Response &response)
	{
		FindStaticResourceInput dto = FindStaticResourceDtoMapper::toDto(request);

		_useCase.execute(dto);
	}
} // namespace http