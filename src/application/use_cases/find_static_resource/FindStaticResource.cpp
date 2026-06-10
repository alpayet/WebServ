/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResource.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:27:44 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/10 19:46:15 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/find_static_resource/FindStaticResource.hpp"
#include "application/ports/IStaticResourceLocator.hpp"
#include "application/ports/IStaticResourceStorage.hpp"
#include "application/use_cases/find_static_resource/FindStaticResourceInput.hpp"
#include "application/use_cases/find_static_resource/FindStaticResourceOutput.hpp"
#include "domain/entities/StaticResource.hpp"

namespace useCase
{
	FindStaticResource::FindStaticResource(
		IStaticResourceLocator &staticResourceLocator, IStaticResourceStorage &staticResourceStorage
	)
		: _staticResourceLocator(staticResourceLocator),
		  _staticResourceStorage(staticResourceStorage)
	{
	}

	FindStaticResourceOutput FindStaticResource::execute(FindStaticResourceInput const &dtoInput)
	{
		std::string storage_path = _staticResourceLocator.locate(dtoInput.id);

		StaticResource static_resource(dtoInput.id, storage_path);

		IStaticResourceReader *resource_reader =
			_staticResourceStorage.createReader(static_resource.getstoragePath());

		return ((FindStaticResourceOutput){.resourceReader = resource_reader});
	}
} // namespace useCase
