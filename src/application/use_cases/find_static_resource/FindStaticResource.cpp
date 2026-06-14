/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResource.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:27:44 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/14 02:07:40 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/find_static_resource/FindStaticResource.hpp"
#include "application/Exception.hpp"
#include "application/ports/IResourceLocator.hpp"
#include "application/ports/IStaticResourcePresenter.hpp"
#include "application/ports/IStaticResourceStorage.hpp"
#include "application/ports/SystemResourceInfos.hpp"
#include "domain/entities/StaticResource.hpp"

namespace app {
namespace useCase {
FindStaticResource::FindStaticResource(
	IResourceLocator		 &resourceLocator,
	IStaticResourceStorage	 &staticResourceStorage,
	IStaticResourcePresenter &staticResourcePresenter
)
	: _resourceLocator(resourceLocator), _staticResourceStorage(staticResourceStorage),
	  _staticResourcePresenter(staticResourcePresenter)
{}

void FindStaticResource::execute(FindStaticResource::Input const &dtoInput)
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

	if (!static_resource.isReadable())
		throw Exception(Exception::readDenied);

	if (static_resource.shouldGenerateListing())
		_staticResourcePresenter.presentListing(static_resource.getStoragePath());
	else
	{
		IStaticResourceReader *resource_reader =
			_staticResourceStorage.createReader(static_resource.getStoragePath());

		_staticResourcePresenter.presentContent(resource_reader);
	}
}
} // namespace useCase

} // namespace app
