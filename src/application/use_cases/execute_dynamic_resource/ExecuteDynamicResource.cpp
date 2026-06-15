/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResource.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/15 23:47:11 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.hpp"
#include "application/Exception.hpp"
#include "application/ports/IDynamicResourceExecutor.hpp"
#include "application/ports/IResourceLocator.hpp"
#include "application/ports/SystemResourceInfos.hpp"
#include "application/ports/presenters/IExecuteDynamicResource.hpp"
#include "domain/entities/DynamicResource.hpp"

namespace app {
namespace useCase {
ExecuteDynamicResource::ExecuteDynamicResource(
	IResourceLocator				 &resourceLocator,
	IDynamicResourceExecutor		 &dynamicResourceExecutor,
	IExecuteDynamicResourcePresenter &executeDynamicResourcePresenter
)
	: _resourceLocator(resourceLocator), _dynamicResourceExecutor(dynamicResourceExecutor),
	  _executeDynamicResourcePresenter(executeDynamicResourcePresenter)
{}

ExecuteDynamicResource::Output
ExecuteDynamicResource::execute(ExecuteDynamicResource::Input const &dtoInput)
{
	SystemResourceInfos target_infos = _resourceLocator.locate(dtoInput.id, dtoInput.rootPath);
	if (!target_infos.exists)
		throw Exception(Exception::notFound);

	domain::ResourceMetaData target_meta_data(
		target_infos.resourcePath, target_infos.type, target_infos.permissions,
		target_infos.contentlength, target_infos.canBeDeleted
	);

	domain::DynamicResource dynamic_resource =
		domain::DynamicResource(dtoInput.id, dtoInput.rootPath, target_meta_data);

	_dynamicResourceExecutor.execute(
		dynamic_resource.getResourcePath(), dtoInput.bodyPath, dtoInput.metaVariables
	);
}
} // namespace useCase
} // namespace app
