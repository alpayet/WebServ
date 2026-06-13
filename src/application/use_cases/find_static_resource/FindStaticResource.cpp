/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResource.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:27:44 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/13 15:13:38 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/find_static_resource/FindStaticResource.hpp"
#include "application/ports/IResourceLocator.hpp"
#include "application/ports/IStaticResourceStorage.hpp"
#include "application/ports/SystemResourceInfos.hpp"
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
	SystemResourceInfos target_infos =
		_resourceLocator.locate(dtoInput.id, dtoInput.routePolicy.rootPath);
	SystemResourceInfos index_infos = _resourceLocator.locate_index(
		dtoInput.routePolicy.indexesId, dtoInput.routePolicy.rootPath
	);

	domain::ResourceMetaData target_meta_data(
		target_infos.storagePath, target_infos.type, target_infos.permissions,
		target_infos.contentlength
	);
	domain::ResourceMetaData index_meta_data(
		index_infos.storagePath, index_infos.type, index_infos.permissions,
		index_infos.contentlength
	);

	domain::StaticResource static_resource(
		dtoInput.id, dtoInput.routePolicy.rootPath, dtoInput.routePolicy.isListingEnabled,
		target_meta_data, index_meta_data
	);

	IStaticResourceReader *resource_reader =
		_staticResourceStorage.createReader(static_resource.getStoragePath());

	return ((FindStaticResource::Output){.resourceReader = resource_reader});
}
} // namespace useCase

} // namespace app
