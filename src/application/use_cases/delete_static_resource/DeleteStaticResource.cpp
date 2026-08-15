/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResource.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:37:49 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/delete_static_resource/DeleteStaticResource.hpp"
#include "application/Exception.hpp"
#include "application/ResourceStatus.hpp"
#include "application/ports/IResourceLocator.hpp"
#include "application/ports/IStaticResourceStorage.hpp"
#include "domain/entities/StaticResource.hpp"

namespace webserv {
namespace app {
namespace useCase {
DeleteStaticResource::DeleteStaticResource(
	IResourceLocator const &resourceLocator, IStaticResourceStorage &staticResourceStorage
)
	: _resourceLocator(resourceLocator), _staticResourceStorage(staticResourceStorage)
{}

void DeleteStaticResource::execute(Input const &dtoInput, IOutputPort &outputPort)
{
	SystemResourceInfo target_infos =
		_resourceLocator.locate(dtoInput.id, dtoInput.matchedRoute, dtoInput.rootPath);
	if (!target_infos.exists)
		throw Exception(Exception::NOT_FOUND);

	domain::ResourceMetaData target_meta_data(
		target_infos.resourcePath, target_infos.type, target_infos.permissions,
		target_infos.resourceSize, target_infos.canBeDeleted
	);
	domain::StaticResource static_resource(dtoInput.id, target_meta_data);

	if (!static_resource.canBeDeleted())
		throw Exception(Exception::ACCESS_DENIED);

	_staticResourceStorage.remove(static_resource.getResourcePath());

	outputPort.presentDeletedResource(DELETED);
}
} // namespace useCase
} // namespace app
}