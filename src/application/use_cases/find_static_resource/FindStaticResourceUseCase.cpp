/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResourceUseCase.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:27:44 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/10 01:12:02 by alpayet          ###   ########.fr       */
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
	std::string storage_path = _staticResourceLocator.locate(dtoInput.id);

	StaticResource static_resource(dtoInput.id, storage_path);

	IStaticResourceReader *resource_reader =
		_staticResourceStorage.createReader(static_resource.getstoragePath());

	return ((FindStaticResourceOutput){.resourceReader = resource_reader});
}
