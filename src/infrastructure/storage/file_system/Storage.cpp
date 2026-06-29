/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Storage.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 04:41:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/29 03:53:59 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/storage/file_system/Storage.hpp"
#include "infrastructure/storage/file_system/Exception.hpp"
#include "infrastructure/storage/file_system/Reader.hpp"
#include <cerrno>
#include <sys/stat.h>
#include <unistd.h>

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
			throw Exception(Exception::fileRemoveFailed);
			break;
	}
}

app::IResourceReader *Storage::createReader(std::string const &resourcePath)
{
	return (new Reader(resourcePath));
}

bool Storage::exists(std::string const &path) { return access(path.c_str(), F_OK) == 0; }

bool Storage::isRegularFile(std::string const &path)
{
	struct stat st;
	return stat(path.c_str(), &st) == 0 && S_ISREG(st.st_mode);
}

bool Storage::isDirectory(std::string const &path)
{
	struct stat st;
	return stat(path.c_str(), &st) == 0 && S_ISDIR(st.st_mode);
}

bool Storage::isReadable(std::string const &path) { return access(path.c_str(), R_OK) == 0; }

bool Storage::isWritable(std::string const &path) { return access(path.c_str(), W_OK) == 0; }

bool Storage::isExecutable(std::string const &path) { return access(path.c_str(), X_OK) == 0; }

std::size_t Storage::getSize(std::string const &path)
{
	struct stat st;
	stat(path.c_str(), &st);
	return st.st_size;
}

bool Storage::isDeletable(std::string const &path)
{
	std::size_t pos = path.find_last_of("/");
	std::string curr_dir;
	if (pos == 0)
		curr_dir = "/";
	else
		curr_dir = path.substr(0, pos);
	return access(curr_dir.c_str(), W_OK | X_OK) == 0;
}
} // namespace fileSystem
