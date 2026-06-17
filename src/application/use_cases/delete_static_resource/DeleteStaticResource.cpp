/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResource.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/18 00:18:58 by alpayet          ###   ########.fr       */
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
	IResourceLocator &resourceLocator, IStaticResourceStorage &staticResourceStorage
)
	: _resourceLocator(resourceLocator), _staticResourceStorage(staticResourceStorage)
{}

void DeleteStaticResource::execute(Input const &dtoInput, IOutputPort &outputPort)
{
	SystemResourceInfos target_infos = _resourceLocator.locate(dtoInput.id, dtoInput.rootPath);
	if (!target_infos.exists)
		throw Exception(Exception::notFound);

	domain::ResourceMetaData target_meta_data(
		target_infos.resourcePath, target_infos.type, target_infos.permissions,
		target_infos.resourceSize, target_infos.canBeDeleted
	);
	domain::StaticResource static_resource(dtoInput.id, dtoInput.rootPath, target_meta_data);

	if (!static_resource.canBeDeleted())
		throw Exception(Exception::accessDenied);

	_staticResourceStorage.remove(static_resource.getResourcePath());
}
} // namespace useCase
} // namespace app