//? access, stat, open, opendir, readdir, closedir

#include "Server/Server.hpp"
#include <string>

std::string	resolveURI(const Location& loc)
{
	return loc.root;    
}

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#include <iostream>
void	displayListing(const Location& loc)
{
	DIR*			dir_ptr = opendir(resolveURI(loc).c_str());
	
	if (!dir_ptr)
	{
		std::cerr << "Couldn't open the '" << loc.root << "' repository" << std::endl;
		return ;
		// throw ();
	}
	struct dirent*	dir = readdir(dir_ptr);
	while (dir != NULL)
	{
		struct stat	st;
		if (stat(dir->d_name, &st) != 0)
		{
			std::cerr << "error stat" << std::endl;
			return ;
		}
		std::cout << dir->d_name << " (" << st.st_size <<  ")" << std::endl;

		dir = readdir(dir_ptr);
	}

	closedir(dir_ptr);
	dir_ptr = NULL;
}

//! directory listing needs resolved uri
// TODO: resolves url (root to replace location, alias-like mapping)
