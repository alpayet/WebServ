/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResourceUseCase.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:27:44 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/09 22:24:20 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/find_static_resource/FindStaticResourceUseCase.hpp"
#include "application/ports/IStaticResourceLocator.hpp"
#include "application/ports/IStaticResourceStorage.hpp"
#include "application/use_cases/find_static_resource/FindStaticResourceInput.hpp"
#include "application/use_cases/find_static_resource/FindStaticResourceOutput.hpp"
#include "domain/entities/StaticResource.hpp"

FindStaticResourceUseCase::FindStaticResourceUseCase(
	IStaticResourceLocator &staticResourceLocator, IStaticResourceStorage &staticResourceStorage
)
	: _staticResourceLocator(staticResourceLocator), _staticResourceStorage(staticResourceStorage)
{
}

FindStaticResourceOutput FindStaticResourceUseCase::execute(FindStaticResourceInput const &dtoInput)
{
	std::string			   storage_path = _staticResourceLocator.locate(dtoInput.id);
	IStaticResourceReader *resource_reader = _staticResourceStorage.createReader(storage_path);

	StaticResource(dtoInput.id, storage_path);

	return ((FindStaticResourceOutput){.resourceReader = resource_reader});
}
