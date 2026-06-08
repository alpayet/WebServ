/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResourceUseCase.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/08 22:21:22 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResourceInput.hpp"
#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResourceOutput.hpp"
#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResourceUseCase.hpp"
#include "domain/entities/StaticResource.hpp"
#include "domain/repositories/IStaticResourceRepository.hpp"

ExecuteDynamicResourceUseCase::ExecuteDynamicResourceUseCase(
	IStaticResourceRepository &staticResourceRepository
)
	: _staticResourceRepository(staticResourceRepository)
{
}

ExecuteDynamicResourceOutput
ExecuteDynamicResourceUseCase::execute(const ExecuteDynamicResourceInput &dtoInput)
{
	_staticResourceRepository.remove(dtoInput.id);
}