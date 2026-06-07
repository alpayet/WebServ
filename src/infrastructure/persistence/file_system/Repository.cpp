/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileSystemRepository.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 23:37:02 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/07 00:53:50 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/persistence/file_system/Repository.hpp"
#include "domain/entities/StaticResource.hpp"
#include "infrastructure/persistence/file_system/IResourceLocator.hpp"

namespace fileSystem
{
	Repository::Repository(IResourceLocator &resourceLocator) : _resourceLocator(resourceLocator) {}

	StaticResource Repository::findById(std::string const &id)
	{
		return (StaticResource(id, _resourceLocator.resolvePhysicalPath(id)));
	}

	IResourceReader *Repository::createReader(const std::string &id) {}
} // namespace fileSystem
