/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResource.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:27:44 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/15 03:22:15 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/serve_static_resource/ServeStaticResource.hpp"
#include "application/Exception.hpp"
#include "application/ports/IResourceLocator.hpp"
#include "application/ports/IStaticResourceStorage.hpp"
#include "application/ports/SystemResourceInfos.hpp"
#include "application/ports/presenters/IServeStaticResourcePresenter.hpp"
#include "domain/entities/StaticResource.hpp"

namespace app {
namespace useCase {
ServeStaticResource::ServeStaticResource(
	IResourceLocator			  &resourceLocator,
	IStaticResourceStorage		  &staticResourceStorage,
	IServeStaticResourcePresenter &serveStaticResourcePresenter
)
	: _resourceLocator(resourceLocator), _staticResourceStorage(staticResourceStorage),
	  _serveStaticResourcePresenter(serveStaticResourcePresenter)
{}

void ServeStaticResource::execute(Input const &dtoInput)
{
	SystemResourceInfos		 target_infos = _resourceLocator.locate(dtoInput.id, dtoInput.rootPath);
	domain::ResourceMetaData target_meta_data(
		target_infos.storagePath, target_infos.type, target_infos.permissions,
		target_infos.contentlength, target_infos.canBeDeleted
	);

	if (target_meta_data.isCollection())
	{
		SystemResourceInfos index_infos =
			_resourceLocator.locateDefaultIndex(dtoInput.indexesId, dtoInput.rootPath);

		if (!index_infos.exists)
			generateListing(dtoInput, target_meta_data);
		else
		{
			domain::ResourceMetaData index_meta_data(
				index_infos.storagePath, index_infos.type, index_infos.permissions,
				index_infos.contentlength, index_infos.canBeDeleted
			);

			if (index_meta_data.isReadable() && !index_meta_data.isCollection())
				serveContent(dtoInput, index_meta_data);
			else
				generateListing(dtoInput, target_meta_data);
		}
	}
	serveContent(dtoInput, target_meta_data);
}

void ServeStaticResource::serveContent(
	Input const &dtoInput, domain::ResourceMetaData const &metaData
)
{
	domain::StaticResource static_resource(dtoInput.id, dtoInput.rootPath, metaData);

	if (!static_resource.isReadable())
		throw Exception(Exception::accessDenied);

	IStaticResourceReader *resource_reader =
		_staticResourceStorage.createReader(static_resource.getStoragePath());
	_serveStaticResourcePresenter.presentContent(resource_reader);
}

void ServeStaticResource::generateListing(
	Input const &dtoInput, domain::ResourceMetaData const &metaData
)
{
	if (!dtoInput.isListingEnabled)
		throw Exception(Exception::listingDisabled);

	domain::StaticResource static_resource(dtoInput.id, dtoInput.rootPath, metaData);

	if (!static_resource.isReadable() || !static_resource.isExecutable())
		throw Exception(Exception::accessDenied);

	_serveStaticResourcePresenter.presentListing(static_resource.getStoragePath());
}
} // namespace useCase
} // namespace app
