/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceUseCase.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/09 22:06:25 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResourceUseCase.hpp"
#include "application/ports/IDynamicResourceExecutor.hpp"
#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResourceInput.hpp"
#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResourceOutput.hpp"
#include "domain/entities/DynamicResource.hpp"

ExecuteDynamicResourceUseCase::ExecuteDynamicResourceUseCase(
	IDynamicResourceExecutor &dynamicResourceExecutor
)
	: _dynamicResourceExecutor(dynamicResourceExecutor)
{
}

ExecuteDynamicResourceOutput
ExecuteDynamicResourceUseCase::execute(ExecuteDynamicResourceInput const &dtoInput)
{
	_dynamicResourceExecutor.execute(dtoInput.id);
}