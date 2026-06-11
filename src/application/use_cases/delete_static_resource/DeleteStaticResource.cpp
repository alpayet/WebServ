/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResource.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/11 17:51:09 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/delete_static_resource/DeleteStaticResource.hpp"
#include "application/ports/IStaticResourceLocator.hpp"
#include "application/ports/IStaticResourceStorage.hpp"
#include "domain/entities/StaticResource.hpp"

namespace useCase
{
	DeleteStaticResource::DeleteStaticResource(
		IStaticResourceLocator &staticResourceLocator, IStaticResourceStorage &staticResourceStorage
	)
		: _staticResourceLocator(staticResourceLocator),
		  _staticResourceStorage(staticResourceStorage)
	{
	}

	DeleteStaticResource::Output
	DeleteStaticResource::execute(DeleteStaticResource::Input const &dtoInput)
	{
		std::string storage_path =
			_staticResourceLocator.locate(dtoInput.id, dtoInput.routePolicy.rootPath);

		_staticResourceStorage.remove(storage_path);
	}
} // namespace useCase