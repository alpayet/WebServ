/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceUseCase.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/10 01:14:05 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResourceUseCase.hpp"
#include "application/ports/IDynamicResourceExecutor.hpp"
#include "application/ports/IDynamicResourceLocator.hpp"
#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResourceInput.hpp"
#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResourceOutput.hpp"
#include "domain/entities/DynamicResource.hpp"

ExecuteDynamicResourceUseCase::ExecuteDynamicResourceUseCase(
	IDynamicResourceExecutor &dynamicResourceExecutor,
	IDynamicResourceLocator	 &dynamicResourceLocator
)
	: _dynamicResourceLocator(dynamicResourceLocator),
	  _dynamicResourceExecutor(dynamicResourceExecutor)
{
}

ExecuteDynamicResourceOutput
ExecuteDynamicResourceUseCase::execute(ExecuteDynamicResourceInput const &dtoInput)
{
	std::string storage_path = _dynamicResourceLocator.locate(dtoInput.id);

	DynamicResource dynamic_resource(dtoInput.id, storage_path);

	_dynamicResourceExecutor.execute(dynamic_resource.getstoragePath(), dtoInput.parameters);
}