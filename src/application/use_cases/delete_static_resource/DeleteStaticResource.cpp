/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResource.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/15 03:22:45 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/delete_static_resource/DeleteStaticResource.hpp"
#include "application/Exception.hpp"
#include "application/ports/IResourceLocator.hpp"
#include "application/ports/IStaticResourceStorage.hpp"
#include "application/ports/SystemResourceInfos.hpp"
#include "application/ports/presenters/IDeleteStaticResourcePresenter.hpp"
#include "domain/entities/StaticResource.hpp"

namespace app {
namespace useCase {
DeleteStaticResource::DeleteStaticResource(
	IResourceLocator			   &resourceLocator,
	IStaticResourceStorage		   &staticResourceStorage,
	IDeleteStaticResourcePresenter &deleteStaticResourcePresenter
)
	: _resourceLocator(resourceLocator), _staticResourceStorage(staticResourceStorage),
	  _deleteStaticResourcePresenter(deleteStaticResourcePresenter)
{}

DeleteStaticResource::Output
DeleteStaticResource::execute(DeleteStaticResource::Input const &dtoInput)
{
	SystemResourceInfos		 target_infos = _resourceLocator.locate(dtoInput.id, dtoInput.rootPath);
	domain::ResourceMetaData target_meta_data(
		target_infos.storagePath, target_infos.type, target_infos.permissions,
		target_infos.contentlength, target_infos.canBeDeleted
	);
	domain::StaticResource static_resource(dtoInput.id, dtoInput.rootPath, target_meta_data);

	if (!static_resource.canBeDeleted())
		throw Exception(Exception::accessDenied);

	_staticResourceStorage.remove(static_resource.getStoragePath());
}
} // namespace useCase
} // namespace app