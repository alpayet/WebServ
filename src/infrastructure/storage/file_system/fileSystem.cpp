/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileSystem.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 03:22:10 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/09 00:11:53 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/storage/file_system/fileSystem.hpp"
#include <sys/stat.h>
#include <unistd.h>

namespace fileSystem {
bool exists(std::string const &path) { return access(path.c_str(), F_OK) == 0; }

bool isRegularFile(std::string const &path)
{
	struct stat st;
	return stat(path.c_str(), &st) == 0 && S_ISREG(st.st_mode);
}

bool isDirectory(std::string const &path)
{
	struct stat st;
	return stat(path.c_str(), &st) == 0 && S_ISDIR(st.st_mode);
}

bool isReadable(std::string const &path) { return access(path.c_str(), R_OK) == 0; }

bool isWritable(std::string const &path) { return access(path.c_str(), W_OK) == 0; }

bool isExecutable(std::string const &path) { return access(path.c_str(), X_OK) == 0; }

std::size_t getSize(std::string const &path)
{
	struct stat st;
	stat(path.c_str(), &st);
	return st.st_size;
}

bool isDeletable(std::string const &path)
{
	std::size_t pos = path.find_last_of("/");
	std::string curr_dir;
	if (pos == 0)
		curr_dir = "/";
	else
		curr_dir = path.substr(0, pos);
	return access(curr_dir.c_str(), W_OK | X_OK) == 0;
}

int close(int &fd)
{
	if (fd >= 0)
	{
		int close_value = close(fd);
		fd = -1;
		return (close_value);
	}
	return (-1);
}

} // namespace fileSytem