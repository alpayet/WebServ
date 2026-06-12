/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResource.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:08:26 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/delete_static_resource/DeleteStaticResource.hpp"
#include "application/ports/IResourceLocator.hpp"
#include "application/ports/IStaticResourceStorage.hpp"
#include "domain/entities/StaticResource.hpp"

namespace app {
namespace useCase {
DeleteStaticResource::DeleteStaticResource(
	IResourceLocator &resourceLocator, IStaticResourceStorage &staticResourceStorage
)
	: _resourceLocator(resourceLocator), _staticResourceStorage(staticResourceStorage)
{}

DeleteStaticResource::Output
DeleteStaticResource::execute(DeleteStaticResource::Input const &dtoInput)
{
	std::string storage_path = _resourceLocator.locate(dtoInput.id, dtoInput.routePolicy.rootPath);

	_staticResourceStorage.remove(storage_path);
}
} // namespace useCase
} // namespace app