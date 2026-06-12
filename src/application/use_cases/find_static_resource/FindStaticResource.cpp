/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResource.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:27:44 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:11:00 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/find_static_resource/FindStaticResource.hpp"
#include "application/ports/IResourceLocator.hpp"
#include "application/ports/IStaticResourceStorage.hpp"
#include "domain/entities/StaticResource.hpp"

namespace app {
namespace useCase {
FindStaticResource::FindStaticResource(
	IResourceLocator &resourceLocator, IStaticResourceStorage &staticResourceStorage
)
	: _resourceLocator(resourceLocator), _staticResourceStorage(staticResourceStorage)
{}

FindStaticResource::Output FindStaticResource::execute(FindStaticResource::Input const &dtoInput)
{
	std::string storage_path = _resourceLocator.locate(dtoInput.id, dtoInput.routePolicy.rootPath);

	StaticResource static_resource(dtoInput.id, storage_path);

	IStaticResourceReader *resource_reader =
		_staticResourceStorage.createReader(static_resource.getstoragePath());

	return ((FindStaticResource::Output){.resourceReader = resource_reader});
}
} // namespace useCase

} // namespace app
