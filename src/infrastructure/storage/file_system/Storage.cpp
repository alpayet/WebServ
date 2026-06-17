/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Storage.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 04:41:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/17 04:29:37 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/storage/file_system/Storage.hpp"
#include "infrastructure/storage/file_system/Exception.hpp"
#include "infrastructure/storage/file_system/Reader.hpp"
#include "infrastructure/storage/file_system/fdReader.hpp"
#include <cerrno>

namespace fileSystem {

void Storage::remove(std::string const &resourcePath)
{
	if (std::remove(resourcePath.c_str()) == 0)
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

app::IResourceReader *Storage::createReader(std::string const &resourcePath)
{
	return (new Reader(resourcePath));
}

app::IResourceReader *Storage::createReader(int const fd) { return (new fdReader(fd)); }
} // namespace fileSystem
