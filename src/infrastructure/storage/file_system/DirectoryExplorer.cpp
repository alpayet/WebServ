/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DirectoryExplorer.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 01:28:15 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/30 19:10:10 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/storage/file_system/DirectoryExplorer.hpp"
#include <cstring>
#include <dirent.h>
#include <fcntl.h>
#include <iterator>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
namespace fileSystem {
std::vector<app::CollectionEntry> DirectoryExplorer::listCollection(
	std::string const &resPath, std::string const &matchedRoute, std::string const &rootPath
)
{
	std::string path = resPath;
	if (path[path.size() - 1] != '/')
		path += "/";

	std::vector<app::CollectionEntry> files;
	DIR								 *dir_ptr = opendir(path.c_str());

	if (!dir_ptr)
	{
		throw std::runtime_error("Couldn't open directory");
	}

	struct tm	   t_local;
	struct dirent *dir = readdir(dir_ptr);
	while (dir != NULL)
	{
		app::CollectionEntry file;
		struct stat			 st;

		if (std::string(dir->d_name) == ".")
		{
			dir = readdir(dir_ptr);
			continue;
		}

		std::string tmpPath;
		if (std::string(dir->d_name) == "..")
		{
			if (path != rootPath)
			{
				file.name = "Previous directory";

				tmpPath = path;
				size_t pos = tmpPath.find_last_of('/');
				if (pos == tmpPath.size() - 1)
				{
					tmpPath.erase(tmpPath.end() - 1);
					pos = tmpPath.find_last_of('/');
				}
				tmpPath.erase(pos);
			}
			else
			{
				dir = readdir(dir_ptr);
				continue ;
			}
		}
		else
		{
			file.name = dir->d_name;
			tmpPath = path + file.name;
		}
		if (!tmpPath.empty())
		{
			if (stat(tmpPath.c_str(), &st) != 0)
			{
				throw std::runtime_error("stat failed on " + tmpPath);
			}

			file.id = tmpPath;
			file.id.replace(0, rootPath.size(), matchedRoute);
		}

		time_t t_mod = st.st_mtime;
		localtime_r(&t_mod, &t_local);
		char t_buf[80];
		bzero(t_buf, 80);
		strftime(t_buf, sizeof(t_buf), "%c", &t_local);
		file.lastMod = t_buf;

		if (S_ISDIR(st.st_mode))
		{
			file.size = "-";
			file.id += "/";
		}
		else
		{
			std::stringstream ss;
			ss << st.st_size;
			file.size = ss.str();
		}

		files.push_back(file);

		dir = readdir(dir_ptr);
	}

	closedir(dir_ptr);
	dir_ptr = NULL;

	return files;
}
} // namespace fileSystem
