
#include "server/Server.hpp"

#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>
#include <limits>
#include <unistd.h>
#include <sys/stat.h>

#include "application/ports/SystemResourceInfos.hpp"
#include "config/Semantic.hpp"


Location Server::findLocationFromUri(std::string const &uri) const
{
	std::size_t pos = 0;
	std::string dir_path = uri;
	while (pos != std::string::npos)
	{
		pos = dir_path.find_last_of('/');
		if (pos != std::string::npos)
			dir_path = dir_path.substr(0, pos);
		std::vector<Location>::const_iterator ite = this->m_locations.end();
		for (std::vector<Location>::const_iterator it = this->m_locations.begin(); it != ite; ++it)
		{
			if (it->path == (dir_path + "/"))
				return *it;
		}
	}
	throw("no corresponding location block");
}

std::vector<std::string> Server::getAllowedMethods(Location const &loc) const
{
	std::vector<std::string> methods;
	if (loc.met_get)
		methods.push_back("GET");
	if (loc.met_post)
		methods.push_back("POST");
	if (loc.met_del)
		methods.push_back("DELETE");
	return (methods);
}

http::RoutePolicy Server::match(std::string const &uri) const
{
	Location loc = findLocationFromUri(uri);

	http::RoutePolicy route;
	route.locPath = loc.path;
	route.rootPath = loc.root;
	route.isListingEnabled = loc.autoindex;
	route.indexesId = loc.index;
	route.allowedMethods = getAllowedMethods(loc);
}
// TODO: use locPath and rootPath
std::string Server::resolvePhysicalPath(
	std::string const &uri, std::string const &locPath, std::string const &rootPath
) const
{
	std::string phy_path;
	if (!rootPath.empty())
		phy_path = rootPath;
	else
		phy_path = m_root + locPath;
	std::size_t pos = uri.find_last_of('/');
	if (pos != std::string::npos)
		phy_path += uri.substr(pos, uri.size() - pos);
	return phy_path;
}

// void param

namespace fileSystem
{
	inline bool exists(const std::string& path)
	{
		return access(path.c_str(), F_OK) == 0;
	}

	inline bool isRegFile(const std::string& path)
	{
		struct stat st;
		return stat(path.c_str(), &st) == 0 && S_ISREG(st.st_mode);
	}

	inline bool isDirectory(const std::string& path)
	{
		struct stat st;
		return stat(path.c_str(), &st) == 0 && S_ISDIR(st.st_mode);
	}

	inline bool isReadable(const std::string& path)
	{
		return access(path.c_str(), R_OK) == 0;
	}

	inline bool isWritable(const std::string& path)
	{
		return access(path.c_str(), W_OK) == 0;
	}

	inline bool isExecutable(const std::string& path)
	{
		return access(path.c_str(), X_OK) == 0;
	}

	inline std::size_t getSize(const std::string& path)
	{
		struct stat st;
		if (stat(path.c_str(), &st) != 0)
			return 0; //throw ("no size");
		return st.st_size;
	}

	bool isDeletable(const std::string& path)
	{
		std::size_t pos = path.find_last_of("/");
		if (pos == std::string::npos)
			return false; // TODO: check that, maybe throw
		std::string curr_dir;
		if (pos == 0)
			curr_dir = "/"
		else
			curr_dir = path.substr(0, pos);
		return access(curr_dir.c_str(), W_OK | X_OK) == 0;
	}
}

// get
app::SystemResourceInfos
Server::locate(std::string const &id, std::string const &locPath, std::string const &rootPath) const
{
	app::SystemResourceInfos sri;

	sri.storagePath = resolvePhysicalPath(id, locPath, rootPath);
	
	if (!fileSystem::exists(sri.storagePath))
	{
		sri.exists = false;
		return sri;
	}
	sri.exists = true;

	if (fileSystem::isRegFile(sri.storagePath))
		sri.type = leaf;
	else if (fileSystem::isDirectory(sri.storagePath))
		sri.type = collection;
	else
		sri.type = unknown;
	
		sri.permissions = 0;
	if (fileSystem::isReadable(sri.storagePath))
		sri.permission += readable;
	if (fileSystem::isWritable(sri.storagePath))
		sri.permission += writable;
	if (fileSystem::isExecutable(sri.storagePath))
		sri.permission += executable;

	sri.content_length = fileSystem::getSize(sri.storagePath);
	
	sri.canBeDeleted = fileSystem::isDeletable(sri.storagePath);

	return app::SystemResourceInfos();
}

// TODO: id = envoyer SystemResourceInfos du 1er index existant
// TODO: if no index in location, check server global index
app::SystemResourceInfos Server::locateDefaultIndex(
	std::vector<std::string> indexesId, std::string const &locPath, std::string const &rootPath
) const
{
	app::SystemResourceInfos sri;

	std::vector<std::string>::const_iterator ite = indexesId.end();
	for (std::vector<std::string>::const_iterator it = indexesId.begin(); it != ite; ++it)
	{
		// TODO: change, it's not the right path
		if (access((rootPath + *it).c_str(), F_OK) == 0)
		{
			sri.storagePath = rootPath + *it;
			return sri;
		}
	}
	return sri;
}

std::string Server::getSupportedHttpVersion(void) const { return ("1.0"); }

std::size_t Server::getMaxRequestLineSize(void) const
{
	return std::numeric_limits<std::size_t>::max();
}

std::size_t Server::getMaxHeaderLineSize(void) const
{
	return std::numeric_limits<std::size_t>::max();
}

std::size_t Server::getMaxHeaderCount(void) const
{
	return std::numeric_limits<std::size_t>::max();
}

std::size_t Server::getMaxBodySize(void) const { return (m_max_body); }

std::size_t Server::getMaxBodySize(std::string const &uri) const
{
	static_cast<void>(uri);
	return (m_max_body);
}


/** DISPLAY FUNCTIONS */
std::ostream &operator<<(std::ostream &os, Location const &l)
{
	os << "\t***LOCATION***" << std::endl;
	os << "\tPath: " << l.path << std::endl;
	os << "\tRoot: " << l.root << std::endl;
	{
		std::vector<std::string>::const_iterator ite = l.index.end();
		for (std::vector<std::string>::const_iterator it = l.index.begin(); it != ite; ++it)
			os << "\tIndex: " << *it << std::endl;
	}
	{
		std::vector<std::string>::const_iterator ite = l.cgi.end();
		for (std::vector<std::string>::const_iterator it = l.cgi.begin(); it != ite; ++it)
			os << "\tCGI: " << *it << std::endl;
	}
	os << "\tMethods: " << std::endl;
	os << std::boolalpha << "\t\tGET= " << l.met_get << std::endl;
	os << std::boolalpha << "\t\tPOST= " << l.met_post << std::endl;
	os << std::boolalpha << "\t\tDEL= " << l.met_del << std::endl;
	os << "\tAutoindex: " << l.autoindex << std::endl;
	os << "\tReturn: " << l.ret << std::endl;
	os << "\t**ENDLOCATION**" << std::endl;

	return os;
}

std::ostream &operator<<(std::ostream &os, Server const &s)
{
	os << "***SERVER***" << std::endl;

	os << "\tPort: " << s.getPort() << std::endl;
	os << "\tInterface: " << s.getInterface() << std::endl;
	os << "\tRoot: " << s.getRoot() << std::endl;
	{
		std::vector<std::string>::const_iterator ite = s.getIndex().end();
		for (std::vector<std::string>::const_iterator it = s.getIndex().begin(); it != ite; ++it)
			os << "\tIndex: " << *it << std::endl;
	}
	os << "\tError pages: " << std::endl;
	{
		std::map<int, std::string>				   err_pages = s.getErrPages();
		std::map<int, std::string>::const_iterator ite = err_pages.end();
		for (std::map<int, std::string>::const_iterator it = err_pages.begin(); it != ite; ++it)
		{
			os << "\t\t" << it->first << " => " << it->second << std::endl;
		}
	}
	os << "\tClient max body size: " << s.getClientMaxBody() << std::endl;
	{
		std::vector<Location>				  locs = s.getLocations();
		std::vector<Location>::const_iterator ite = locs.end();
		for (std::vector<Location>::const_iterator it = locs.begin(); it != ite; ++it)
		{
			os << *it;
		}
	}
	os << "**ENDSERVER**" << std::endl;

	return os;
}
