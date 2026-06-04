//? access, stat, open, opendir, readdir, closedir

#include "Server/Server.hpp"
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>



std::string	resolveURI(const Location& loc)
{
	std::string	uri;
	
	for (size_t i = 0 ; i < loc.index.size() ; ++i)
	{
		int fd = open((loc.root + loc.index[i]).c_str(), O_RDONLY);
		if (fd > 0)
		{
			uri = loc.root + loc.index[i];
			close(fd);
			return uri;
		}
	}
	DIR*	dir_ptr = opendir(loc.root.c_str());
	if (dir_ptr)
		uri = loc.root;
	else
		; // TODO: uri = error_page 403; 
	return uri;
}

// TODO: no size for directory && add date && rename ".." to "parent directory"
#include <iostream>
void	displayListing(std::string dir_name)
{
	DIR*			dir_ptr = opendir(dir_name.c_str());
	
	// TODO: generate GET method
	/**
	 * call get
	 * if ok -> 200
	 * if opendir fail -> 500
	 * 
	 * html to generate:
	 * <h1>"Index of " + current directory</h1>
	 * "Name\tLast modified\tSize"
	 * <ul>
	 * <li><a href="..">Previous folder</a>[tab] st.st_mtime [tab] - </li>
	 * while (read file)
	 * 		if file
	 * 			<li><a href="filename">filename [tab] st.st_mtime [tab] st.st_size</a></li>
	 * 		else if directory
	 * 			<li><a href="filename">filename [tab] st.st_mtime [tab] -</a></li>
	 * </ul>
	 * 
	 */

	if (!dir_ptr)
	{
		std::cerr << "Couldn't open the '" << dir_name << "' repository" << std::endl;
		return ;
		// throw ();
	}


	std::cout << "<h1>Index of " << dir_name << "</h1>" << std::endl;
	std::cout << "<table>" << std::endl;
	std::cout << "\t<tr>" << std::endl;
	std::cout << "\t\t<th>Name</th>" << std::endl;
	std::cout << "\t\t<th>Last Modified</th>" << std::endl;
	std::cout << "\t\t<th>Size</th>" << std::endl;
	std::cout << "\t</tr>" << std::endl;

	struct dirent*	dir = readdir(dir_ptr);
	struct stat	st;
	time_t	t_mod = st.st_mtime;
	if (stat(dir->d_name, &st) != 0)
	{
		std::cerr << "error stat" << std::endl;
		return ;
		// throw ();
	}
	// TODO: seek ".." and go back to beginning
	struct tm	t_local;
	localtime_r(&t_mod, &t_local);
	char	t_buf[80];
	strftime(t_buf, sizeof(t_buf), "%c", &t_local);
	std::cout << "\t<tr>" << std::endl;
	size_t	pos = dir_name.find_last_of('/');
	if (pos == dir_name.size() - 1)
	{
		dir_name.erase(dir_name.end() - 1);
		pos = dir_name.find_last_of('/');
	}
	std::string	prev_dir = dir_name.substr(0, pos);
	std::cout << "\t\t<td><a href=\"" << prev_dir << "\">Previous directory</a></td>" << std::endl;
	std::cout << "\t\t<td>" << t_buf << "</td>" << std::endl;
	std::cout << "\t\t<td>-</td>" << std::endl;
	std::cout << "\t</tr>" << std::endl;
	dir = readdir(dir_ptr);
	while (dir != NULL)
	{
		if (std::string(dir->d_name) == "." || std::string(dir->d_name) == "..")
		{
			dir = readdir(dir_ptr);
			continue ;
		}
		bzero(t_buf, 80);
		std::cout << "\t<tr>" << std::endl;
		std::cout << "\t\t<td><a href=\"" << dir->d_name << "\">" << dir->d_name << "</a></td>" << std::endl;
		t_mod = st.st_mtime;
		localtime_r(&t_mod, &t_local);
		strftime(t_buf, sizeof(t_buf), "%c", &t_local);
		std::cout << "\t\t<td>" << t_buf << "</td>" << std::endl;
		if (st.st_mode & S_IFDIR)
			std::cout << "\t\t<td>-</td>" << std::endl;
		else
			std::cout << "\t\t<td>" << st.st_size << "</td>" << std::endl;
		std::cout << "\t</tr>" << std::endl;
		if (stat(dir->d_name, &st) != 0)
		{
			std::cerr << "error stat" << std::endl;
			return ;
			// throw ();
		}
		dir = readdir(dir_ptr);
	}

	std::cout << "</table>" << std::endl;
	closedir(dir_ptr);
	dir_ptr = NULL;
}

//! directory listing needs resolved uri
// TODO: resolves url (root to replace location, alias-like mapping)


