/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResource.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/10 17:54:53 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/delete_static_resource/DeleteStaticResource.hpp"
#include "application/ports/IStaticResourceLocator.hpp"
#include "application/ports/IStaticResourceStorage.hpp"
#include "application/use_cases/delete_static_resource/DeleteStaticResourceInput.hpp"
#include "application/use_cases/delete_static_resource/DeleteStaticResourceOutput.hpp"
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

	DeleteStaticResourceOutput
	DeleteStaticResource::execute(DeleteStaticResourceInput const &dtoInput)
	{
		std::string storage_path = _staticResourceLocator.locate(dtoInput.id);

		_staticResourceStorage.remove(storage_path);
	}
} // namespace useCase