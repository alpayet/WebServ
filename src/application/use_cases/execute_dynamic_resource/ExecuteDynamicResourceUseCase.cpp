/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceUseCase.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/08 23:12:59 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResourceUseCase.hpp"
#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResourceInput.hpp"
#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResourceOutput.hpp"
#include "domain/entities/StaticResource.hpp"
#include "domain/repositories/IStaticResourceRepository.hpp"

ExecuteDynamicResourceUseCase::ExecuteDynamicResourceUseCase(
	IStaticResourceRepository &staticResourceRepository
)
	: _staticResourceRepository(staticResourceRepository)
{
}

ExecuteDynamicResourceOutput
ExecuteDynamicResourceUseCase::execute(ExecuteDynamicResourceInput const &dtoInput)
{
	_staticResourceRepository.remove(dtoInput.id);
}