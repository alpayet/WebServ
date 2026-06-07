/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResourceUseCase.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/07 21:29:50 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/delete_static_resource/DeleteStaticResourceUseCase.hpp"
#include "application/use_cases/delete_static_resource/DeleteStaticResourceInput.hpp"
#include "application/use_cases/delete_static_resource/DeleteStaticResourceOutput.hpp"
#include "domain/entities/StaticResource.hpp"
#include "domain/repositories/IStaticResourceRepository.hpp"

DeleteStaticResourceUseCase::DeleteStaticResourceUseCase(
	IStaticResourceRepository &staticResourceRepository
)
	: _staticResourceRepository(staticResourceRepository)
{
}

DeleteStaticResourceOutput
DeleteStaticResourceUseCase::execute(const DeleteStaticResourceInput &dtoInput)
{
}