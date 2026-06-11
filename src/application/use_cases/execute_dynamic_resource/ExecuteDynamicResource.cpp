/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResource.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/11 19:52:21 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.hpp"
#include "application/ports/IDynamicResourceExecutor.hpp"
#include "application/ports/IresourceLocator.hpp"
#include "domain/entities/DynamicResource.hpp"

namespace useCase
{
	ExecuteDynamicResource::ExecuteDynamicResource(
		IDynamicResourceExecutor &dynamicResourceExecutor, IresourceLocator &resourceLocator
	)
		: _resourceLocator(resourceLocator), _dynamicResourceExecutor(dynamicResourceExecutor)
	{
	}

	ExecuteDynamicResource::Output
	ExecuteDynamicResource::execute(ExecuteDynamicResource::Input const &dtoInput)
	{
		std::string storage_path =
			_resourceLocator.locate(dtoInput.id, dtoInput.routePolicy.rootPath);

		DynamicResource dynamic_resource(dtoInput.id, storage_path);

		_dynamicResourceExecutor.execute(dynamic_resource.getstoragePath(), dtoInput.metaVariables);
	}
} // namespace useCase
