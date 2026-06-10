/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceController.cpp               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:30:26 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/10 19:45:20 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/controllers/ExecuteDynamicResourceController.hpp"
#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.hpp"
#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResourceInput.hpp"
#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResourceOutput.hpp"
#include "infrastructure/http/Request.hpp"
#include "infrastructure/http/Response.hpp"
#include "infrastructure/http/mappers/ExecuteDynamicResourceDtoMapper.hpp"

namespace http
{
	ExecuteDynamicResourceController::ExecuteDynamicResourceController(
		useCase::ExecuteDynamicResource &useCase
	)
		: _useCase(useCase)
	{
	}

	void ExecuteDynamicResourceController::operator()(Request const &request, Response &response)
	{
		ExecuteDynamicResourceInput dto = ExecuteDynamicResourceDtoMapper::toDto(request);

		_useCase.execute(dto);
	}
} // namespace http