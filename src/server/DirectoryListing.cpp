//? access, stat, open, opendir, readdir, closedir

#include "server/Server.hpp"
#include <cstring>
#include <dirent.h>
#include <fcntl.h>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

/**
 * divide into 4 functions
 * fileSystem opendir
 * function to populate vector of fileInfos struct
 * function to get curr directory name -> careful with last "/", can be missing
 * display function
 */

struct fileInfos
{
	std::string name;
	char[80] lastMod;
	std::size_t size;
};

std::vector<fileInfos> getFileInfos(std::string path)
{
	DIR *dir_ptr = opendir(path.c_str());

	if (!dir_ptr)
	{
		throw("banana");
	}
	std::ostringstream oss;

	oss << "<!DOCTYPE html>" << std::endl;
	oss << "<html>" << std::endl;
	oss << "<head>" << std::endl;
	oss << "<title>Directory listing</title>" << std::endl;
	oss << "</head>" << std::endl;
	oss << "<h1>Index of " << path << "</h1>" << std::endl; // TODO: change that
	oss << "<table>" << std::endl;
	oss << "\t<tr>" << std::endl;
	oss << "\t\t<th>Name</th>" << std::endl;
	oss << "\t\t<th>Last Modified</th>" << std::endl;
	oss << "\t\t<th>Size</th>" << std::endl;
	oss << "\t</tr>" << std::endl;

	struct dirent *dir = readdir(dir_ptr);
	struct stat	   st;
	time_t		   t_mod = st.st_mtime;
	if (stat(dir->d_name, &st) != 0)
	{
		throw("banana");
	}
	struct tm t_local;
	localtime_r(&t_mod, &t_local);
	char t_buf[80];
	strftime(t_buf, sizeof(t_buf), "%c", &t_local);
	oss << "\t<tr>" << std::endl;
	size_t pos = dir_name.find_last_of('/');
	if (pos == dir_name.size() - 1)
	{
		dir_name.erase(dir_name.end() - 1);
		pos = dir_name.find_last_of('/');
	}
	std::string prev_dir = dir_name.substr(0, pos);
	oss << "\t\t<td><a href=\"" << prev_dir << "\">Previous directory</a></td>" << std::endl;
	oss << "\t\t<td>" << t_buf << "</td>" << std::endl;
	oss << "\t\t<td>-</td>" << std::endl;
	oss << "\t</tr>" << std::endl;
	dir = readdir(dir_ptr);
	while (dir != NULL)
	{
		if (std::string(dir->d_name) == "." || std::string(dir->d_name) == "..")
		{
			dir = readdir(dir_ptr);
			continue;
		}
		bzero(t_buf, 80);
		oss << "\t<tr>" << std::endl;
		oss << "\t\t<td><a href=\"" << dir->d_name << "\">" << dir->d_name << "</a></td>"
			<< std::endl;
		t_mod = st.st_mtime;
		localtime_r(&t_mod, &t_local);
		strftime(t_buf, sizeof(t_buf), "%c", &t_local);
		oss << "\t\t<td>" << t_buf << "</td>" << std::endl;
		if (S_ISDIR(st.st_mode))
			oss << "\t\t<td>-</td>" << std::endl;
		else
			oss << "\t\t<td>" << st.st_size << "</td>" << std::endl;
		oss << "\t</tr>" << std::endl;
		if (stat(dir->d_name, &st) != 0)
		{
			throw("banana");
		}
		dir = readdir(dir_ptr);
	}

	oss << "</table>" << std::endl;
	oss << "</body>" << std::endl;
	oss << "</html>" << std::endl;
	closedir(dir_ptr);
	dir_ptr = NULL;
	return oss;
}

// TODO: no size for directory && add date && rename ".." to "parent directory"
std::string displayListing(std::string dir_name)
{
	DIR *dir_ptr = opendir(dir_name.c_str());

	// TODO: generate GET method
	// TODO: check before
	if (!dir_ptr)
	{
		throw("banana");
	}
	std::ostringstream oss;

	oss << "<!DOCTYPE html>" << std::endl;
	oss << "<html>" << std::endl;
	oss << "<head>" << std::endl;
	oss << "<title>Directory listing</title>" << std::endl;
	oss << "</head>" << std::endl;
	oss << "<h1>Index of " << dir_name << "</h1>" << std::endl;
	oss << "<table>" << std::endl;
	oss << "\t<tr>" << std::endl;
	oss << "\t\t<th>Name</th>" << std::endl;
	oss << "\t\t<th>Last Modified</th>" << std::endl;
	oss << "\t\t<th>Size</th>" << std::endl;
	oss << "\t</tr>" << std::endl;

	struct dirent *dir = readdir(dir_ptr);
	struct stat	   st;
	time_t		   t_mod = st.st_mtime;
	if (stat(dir->d_name, &st) != 0)
	{
		throw("banana");
	}
	struct tm t_local;
	localtime_r(&t_mod, &t_local);
	char t_buf[80];
	strftime(t_buf, sizeof(t_buf), "%c", &t_local);
	oss << "\t<tr>" << std::endl;
	size_t pos = dir_name.find_last_of('/');
	if (pos == dir_name.size() - 1)
	{
		dir_name.erase(dir_name.end() - 1);
		pos = dir_name.find_last_of('/');
	}
	std::string prev_dir = dir_name.substr(0, pos);
	oss << "\t\t<td><a href=\"" << prev_dir << "\">Previous directory</a></td>" << std::endl;
	oss << "\t\t<td>" << t_buf << "</td>" << std::endl;
	oss << "\t\t<td>-</td>" << std::endl;
	oss << "\t</tr>" << std::endl;
	dir = readdir(dir_ptr);
	while (dir != NULL)
	{
		if (std::string(dir->d_name) == "." || std::string(dir->d_name) == "..")
		{
			dir = readdir(dir_ptr);
			continue;
		}
		bzero(t_buf, 80);
		oss << "\t<tr>" << std::endl;
		oss << "\t\t<td><a href=\"" << dir->d_name << "\">" << dir->d_name << "</a></td>"
			<< std::endl;
		t_mod = st.st_mtime;
		localtime_r(&t_mod, &t_local);
		strftime(t_buf, sizeof(t_buf), "%c", &t_local);
		oss << "\t\t<td>" << t_buf << "</td>" << std::endl;
		if (S_ISDIR(st.st_mode))
			oss << "\t\t<td>-</td>" << std::endl;
		else
			oss << "\t\t<td>" << st.st_size << "</td>" << std::endl;
		oss << "\t</tr>" << std::endl;
		if (stat(dir->d_name, &st) != 0)
		{
			throw("banana");
		}
		dir = readdir(dir_ptr);
	}

	oss << "</table>" << std::endl;
	oss << "</body>" << std::endl;
	oss << "</html>" << std::endl;
	closedir(dir_ptr);
	dir_ptr = NULL;
	return oss;
}
