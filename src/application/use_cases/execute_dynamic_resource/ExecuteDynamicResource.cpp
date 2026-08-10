/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResource.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/09 23:07:11 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.hpp"
#include "application/Exception.hpp"
#include "application/ports/IDynamicResourceExecutor.hpp"
#include "application/ports/IResourceLocator.hpp"
#include "application/ports/SystemResourceInfo.hpp"
#include "domain/entities/DynamicResource.hpp"

namespace app {
namespace useCase {
ExecuteDynamicResource::ExecuteDynamicResource(
	IResourceLocator const &resourceLocator, IDynamicResourceExecutor &dynamicResourceExecutor
)
	: _resourceLocator(resourceLocator), _dynamicResourceExecutor(dynamicResourceExecutor)
{}

void ExecuteDynamicResource::execute(Input const &dtoInput, IOutputPort &outputPort)
{
	SystemResourceInfo target_infos =
		_resourceLocator.locate(dtoInput.id, dtoInput.matchedRoute, dtoInput.rootPath);
	if (!target_infos.exists)
		throw Exception(Exception::NOT_FOUND);

	domain::ResourceMetaData target_meta_data(
		target_infos.resourcePath, target_infos.type, target_infos.permissions,
		target_infos.resourceSize, target_infos.canBeDeleted
	);

	domain::DynamicResource dynamic_resource(dtoInput.id, target_meta_data);

	if (!dynamic_resource.isReadable() || !dynamic_resource.isExecutable())
		throw Exception(Exception::ACCESS_DENIED);

	int	stream_id = _dynamicResourceExecutor.execute(
		dynamic_resource.getResourcePath(), dtoInput.bodyPath, dtoInput.metaVariables
	);

	outputPort.presentStream(stream_id);
}
} // namespace useCase
} // namespace app
