/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResourceUseCase.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:27:44 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/07 20:11:35 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/find_static_resource/FindStaticResourceUseCase.hpp"
#include "application/ports/IStaticResourceReaderProvider.hpp"
#include "application/use_cases/find_static_resource/FindStaticResourceInput.hpp"
#include "application/use_cases/find_static_resource/FindStaticResourceOutput.hpp"
#include "domain/entities/StaticResource.hpp"
#include "domain/repositories/IStaticResourceRepository.hpp"

FindStaticResourceUseCase::FindStaticResourceUseCase(
	IStaticResourceRepository	  &staticResourceRepository,
	IStaticResourceReaderProvider &staticResourceReaderProvider
)
	: _staticResourceRepository(staticResourceRepository),
	  _staticResourceReaderProvider(staticResourceReaderProvider)
{
}

FindStaticResourceOutput FindStaticResourceUseCase::execute(const FindStaticResourceInput &dtoInput)
{
	StaticResource	 static_resource = _staticResourceRepository.findById(dtoInput.id);
	IResourceReader *resourceReader =
		_staticResourceReaderProvider.createReader(static_resource.getStorageLocation());

	return ((FindStaticResourceOutput){.resourceReader = resourceReader});
}
