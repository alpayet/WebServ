/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Storage.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 04:41:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:33:37 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/storage/file_system/Storage.hpp"
#include "infrastructure/storage/file_system/Exception.hpp"
#include "infrastructure/storage/file_system/Reader.hpp"
#include <cerrno>

namespace fileSystem {

void fileSystem::Storage::remove(std::string const &storagePath)
{
	if (std::remove(storagePath.c_str()) == 0)
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

app::IStaticResourceReader *Storage::createReader(std::string const &storagePath)
{
	return (new Reader(storagePath));
}
} // namespace fileSystem
