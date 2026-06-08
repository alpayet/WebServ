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
#include "infrastructure/persistence/file_system/Exception.hpp"
#include "infrastructure/persistence/file_system/IResourceLocator.hpp"
#include "infrastructure/persistence/file_system/Reader.hpp"
#include <cerrno>

namespace fileSystem
{
	Repository::Repository(IResourceLocator &resourceLocator) : _resourceLocator(resourceLocator) {}

	StaticResource Repository::findById(std::string const &id)
	{
		return (StaticResource(id, _resourceLocator.resolvePhysicalPath(id)));
	}

	void fileSystem::Repository::remove(const std::string &id)
	{
		std::string physical_path = _resourceLocator.resolvePhysicalPath(id);

		if (std::remove(physical_path.c_str()) == 0)
			return;
		switch (errno)
		{
			case ENOENT:
				throw Exception(Exception::fileNotFound);
				break;
			case EACCES:
			case EPERM:
				throw Exception(Exception::permissionDenied);
				break;
			default:
				throw Exception(Exception::internalErrorFileUnlinkFailed);
				break;
		}
	}

	IResourceReader *Repository::createReader(const std::string &storageLocation)
	{
		return (new Reader(storageLocation));
	}
} // namespace fileSystem
