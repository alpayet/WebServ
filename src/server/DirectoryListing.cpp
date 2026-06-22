//? access, stat, open, opendir, readdir, closedir

#include "server/Server.hpp"
#include <cstring>
#include <dirent.h>
#include <fcntl.h>
#include <iterator>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

struct fileInfos
{
	std::string name;
	std::string lastMod;
	std::string size;
	std::string uri;
};

std::string getHeader(std::string const &path)
{
	std::string header;

	header += "<!DOCTYPE html>\n";
	header += "<html>\n";
	header += "<head>\n";
	header += "<title>Directory listing</title>\n";
	header += "<style type=\"text/css\">\n";
	header += "td { padding: 0 15px; }\n";
	header += "</style>\n";
	header += "</head>\n";
	header += "<h1>Index of " + path + "</h1>\n";
	header += "<table>\n";
	header += "\t<tr>\n";
	header += "\t\t<th>Name</th>\n";
	header += "\t\t<th>Last Modified</th>\n";
	header += "\t\t<th>Size</th>\n";
	header += "\t</tr>\n";

	return header;
}

//! phyPath always pass with trailing "/"
// TODO: check phyPath contains rootPath before calling
// ? normally the case
std::vector<fileInfos>
getFileInfos(std::string const &phyPath, std::string const &locPath, std::string const &rootPath)
{
	std::vector<fileInfos> files;
	DIR					  *dir_ptr = opendir(phyPath.c_str());

	if (!dir_ptr)
	{
		throw std::runtime_error("Couldn't open directory");
	}

	struct tm	   t_local;
	struct dirent *dir = readdir(dir_ptr);
	while (dir != NULL)
	{
		fileInfos	file;
		struct stat st;

		if (std::string(dir->d_name) == ".")
		{
			dir = readdir(dir_ptr);
			continue;
		}

		std::string tmpPath;
		if (std::string(dir->d_name) == "..")
		{
			if (phyPath != rootPath)
			{
				file.name = "Previous directory";

				tmpPath = phyPath;
				size_t pos = tmpPath.find_last_of('/');
				if (pos == tmpPath.size() - 1)
				{
					tmpPath.erase(tmpPath.end() - 1);
					pos = tmpPath.find_last_of('/');
				}
				tmpPath.erase(pos);
			}
		}
		else
		{
			file.name = dir->d_name;
			tmpPath = phyPath + file.name;
		}
		if (!tmpPath.empty())
		{
			if (stat(tmpPath.c_str(), &st) != 0)
			{
				throw std::runtime_error("stat failed on " + tmpPath);
			}

			file.uri = tmpPath;
			file.uri.replace(0, rootPath.size(), locPath);
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
			file.uri += "/";
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

std::string getListing(std::string uri, std::vector<fileInfos> files)
{
	std::string listing;

	listing = getHeader(uri);

	std::vector<fileInfos>::const_iterator ite = files.end();
	std::vector<fileInfos>::const_iterator it = files.begin();
	for (; it != ite; ++it)
	{
		if (!it->name.empty())
		{
			listing += "\t<tr>\n";
			listing += "\t\t<td><a href=\"" + it->uri + "\">" + it->name + "</a></td>\n";
			listing += "\t\t<td>" + it->lastMod + "</td>\n";
			listing += "\t\t<td>" + it->size + "</td>\n";
			listing += "\t</tr>\n";
		}
	}

	listing += "</table>\n";
	listing += "</body>\n";
	listing += "</html>\n";

	return listing;
}

/**
 * moi je vérifie si id finit par un "/"
 * si c'est pas le cas
 * je le rajoute pour que ça fonctionne bien dans notre logique qu'un uri de dossier finisse par "/"
 * je resolve le physical path
 * je génère le listing (tout l'html du doctype au </html>)
 * tu débrouilles avec la string
 */
std::string directoryListing(
	Server const	  &server,
	std::string const &id,
	std::string const &matchedRoute,
	std::string const &rootPath
)
{
	std::string uri = id;
	if (id[id.size() - 1] != '/')
		uri += "/";

	std::string phyPath = server.resolvePhysicalPath(id, matchedRoute, rootPath);
}
