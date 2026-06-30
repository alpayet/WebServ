/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResource.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:27:44 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/30 17:01:20 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/serve_static_resource/ServeStaticResource.hpp"
#include "application/Exception.hpp"
// #include "application/ports/ICollectionExplorer.hpp"
#include "application/ports/IResourceLocator.hpp"
#include "application/ports/IStaticResourceStorage.hpp"
#include "domain/entities/StaticResource.hpp"

namespace app {
namespace useCase {
ServeStaticResource::ServeStaticResource(
	IResourceLocator &resourceLocator, IStaticResourceStorage &staticResourceStorage
	// ICollectionExplorer	   &collectionExplorer
)
	: _resourceLocator(resourceLocator), _staticResourceStorage(staticResourceStorage)
//   _collectionExplorer(collectionExplorer)
{}

void ServeStaticResource::execute(Input const &dtoInput, IOutputPort &outputPort)
{
	SystemResourceInfo target_infos =
		_resourceLocator.locate(dtoInput.id, dtoInput.matchedRoute, dtoInput.rootPath);
	if (!target_infos.exists)
		throw Exception(Exception::notFound);

	domain::ResourceMetaData target_meta_data(
		target_infos.resourcePath, target_infos.type, target_infos.permissions,
		target_infos.resourceSize, target_infos.canBeDeleted
	);

	if (target_meta_data.isCollection())
	{
		SystemResourceInfo index_infos = _resourceLocator.locateDefaultIndex(
			dtoInput.indexesId, dtoInput.matchedRoute, dtoInput.rootPath
		);

		if (!index_infos.exists)
			generateListing(dtoInput, outputPort, target_meta_data);
		else
		{
			domain::ResourceMetaData index_meta_data(
				index_infos.resourcePath, index_infos.type, index_infos.permissions,
				index_infos.resourceSize, index_infos.canBeDeleted
			);

			if (index_meta_data.isReadable() && !index_meta_data.isCollection())
				serveContent(dtoInput, outputPort, index_meta_data);
			else
				generateListing(dtoInput, outputPort, target_meta_data);
		}
	}
	serveContent(dtoInput, outputPort, target_meta_data);
}

void ServeStaticResource::serveContent(
	Input const &dtoInput, IOutputPort &outputPort, domain::ResourceMetaData const &metaData
)
{
	domain::StaticResource static_resource(dtoInput.id, metaData);

	if (!static_resource.isReadable())
		throw Exception(Exception::accessDenied);

	IResourceReader *resource_reader =
		_staticResourceStorage.createReader(static_resource.getResourcePath());
	outputPort.presentContent(found, static_resource.getResourceSize(), resource_reader);
}

void ServeStaticResource::generateListing(
	Input const &dtoInput, IOutputPort &outputPort, domain::ResourceMetaData const &metaData
)
{
	// if (!dtoInput.isListingEnabled)
	// 	throw Exception(Exception::listingDisabled);

	// domain::StaticResource static_resource(dtoInput.id, dtoInput.rootPath, metaData);

	// if (!static_resource.isReadable() || !static_resource.isExecutable())
	// 	throw Exception(Exception::accessDenied);

	// // TODO: voir pour la gestion du listing si contenue d ulisting dans fichier ou direct en ram
	// std::vector<char> collection_data =
	// 	_collectionExplorer.listCollection(static_resource.getResourcePath());

	// outputPort.presentListing(resourceFound, collection_data);
}
} // namespace useCase
} // namespace app
