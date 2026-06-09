/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Storage.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 04:41:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/09 04:50:04 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/storage/file_system/Storage.hpp"
#include "infrastructure/storage/file_system/Exception.hpp"
#include "infrastructure/storage/file_system/Reader.hpp"
#include <cerrno>

namespace fileSystem
{

	void fileSystem::Storage::remove(std::string const &storageLocation)
	{
		if (std::remove(storageLocation.c_str()) == 0)
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

	IResourceReader *Storage::createReader(std::string const &storageLocation)
	{
		return (new Reader(storageLocation));
	}
} // namespace fileSystem
