/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResource.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/14 01:25:44 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/delete_static_resource/DeleteStaticResource.hpp"
#include "application/ports/IResourceLocator.hpp"
#include "application/ports/IStaticResourceStorage.hpp"
#include "domain/entities/StaticResource.hpp"

namespace app {
namespace useCase {
DeleteStaticResource::DeleteStaticResource(
	IResourceLocator &resourceLocator, IStaticResourceStorage &staticResourceStorage
)
	: _resourceLocator(resourceLocator), _staticResourceStorage(staticResourceStorage)
{}

DeleteStaticResource::Output
DeleteStaticResource::execute(DeleteStaticResource::Input const &dtoInput)
{
	SystemResourceInfos target_infos =
		_resourceLocator.locate(dtoInput.id, dtoInput.routePolicy.rootPath);
	SystemResourceInfos index_infos = _resourceLocator.locateDefaultIndex(
		dtoInput.routePolicy.indexesId, dtoInput.routePolicy.rootPath
	);

	domain::ResourceMetaData target_meta_data(
		target_infos.storagePath, target_infos.type, target_infos.permissions,
		target_infos.contentlength, target_infos.canBeDeleted
	);
	domain::ResourceMetaData index_meta_data(
		index_infos.storagePath, index_infos.type, index_infos.permissions,
		index_infos.contentlength, index_infos.canBeDeleted
	);

	domain::StaticResource static_resource(
		dtoInput.id, dtoInput.routePolicy.rootPath, dtoInput.routePolicy.isListingEnabled,
		target_meta_data, index_meta_data
	);
	_staticResourceStorage.remove(storage_path);
}
} // namespace useCase
} // namespace app