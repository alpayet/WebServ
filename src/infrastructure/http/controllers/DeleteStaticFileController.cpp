/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticFileController.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:30:26 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/07 21:37:28 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/delete_static_resource/DeleteStaticResourceInput.hpp"
#include "application/use_cases/find_static_resource/FindStaticResourceOutput.hpp"
#include "application/use_cases/delete_static_resource/DeleteStaticResourceUseCase.hpp"
#include "infrastructure/http/Request.hpp"
#include "infrastructure/http/Response.hpp"
#include "infrastructure/http/controllers/DeleteStaticResourceController.hpp"
#include "infrastructure/http/mappers/DeleteStaticResourceDtoMapper.hpp"

namespace http
{
	DeleteStaticResourceController::DeleteStaticResourceController(
		DeleteStaticResourceUseCase &useCase
	)
		: _useCase(useCase)
	{
	}

	void DeleteStaticResourceController::operator()(const Request &request, Response &response)
	{
		DeleteStaticResourceInput dto = DeleteStaticResourceDtoMapper::toDto(request);

		_useCase.execute(dto);
	}
} // namespace http