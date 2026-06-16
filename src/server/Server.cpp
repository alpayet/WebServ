
#include "server/Server.hpp"

#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

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
	if (!loc.index.empty())
		route.indexesId = loc.index;
	else
		route.indexesId = m_index;
	route.allowedMethods = getAllowedMethods(loc);
	return route;
}

std::string Server::resolvePhysicalPath(
	std::string const &uri, std::string const &locPath, std::string const &rootPath
) const
{
	std::string path;
	if (rootPath.empty())
		path = m_root + locPath.substr(1, locPath.size() - 1);
	else
		path = rootPath;
	std::string resUri = uri;
	resUri.replace(0, locPath.size(), path);
	return resUri;
}

namespace fileSystem {
inline bool exists(std::string const &path) { return access(path.c_str(), F_OK) == 0; }

inline bool isRegularFile(std::string const &path)
{
	struct stat st;
	return stat(path.c_str(), &st) == 0 && S_ISREG(st.st_mode);
}

inline bool isDirectory(std::string const &path)
{
	struct stat st;
	return stat(path.c_str(), &st) == 0 && S_ISDIR(st.st_mode);
}

inline bool isReadable(std::string const &path) { return access(path.c_str(), R_OK) == 0; }

inline bool isWritable(std::string const &path) { return access(path.c_str(), W_OK) == 0; }

inline bool isExecutable(std::string const &path) { return access(path.c_str(), X_OK) == 0; }

inline std::size_t getSize(std::string const &path)
{
	struct stat st;
	if (stat(path.c_str(), &st) != 0)
		return 0; // throw ("no size");
	return st.st_size;
}

bool isDeletable(std::string const &path)
{
	std::size_t pos = path.find_last_of("/");
	if (pos == std::string::npos)
		return false; // TODO: check that, maybe throw
	std::string curr_dir;
	if (pos == 0)
		curr_dir = "/";
	else
		curr_dir = path.substr(0, pos);
	return access(curr_dir.c_str(), W_OK | X_OK) == 0;
}
} // namespace fileSystem

app::SystemResourceInfos setSRI(std::string const &path)
{
	app::SystemResourceInfos sri;

	sri.resourcePath = path;

	if (!fileSystem::exists(sri.resourcePath))
	{
		sri.exists = false;
		return sri; // TODO: check if need to set other values
	}
	sri.exists = true;

	if (fileSystem::isRegularFile(sri.resourcePath))
		sri.type = domain::leaf;
	else if (fileSystem::isDirectory(sri.resourcePath))
		sri.type = domain::collection;
	else
		sri.type = domain::unknown;

	sri.permissions = domain::none;
	if (fileSystem::isReadable(sri.resourcePath))
		sri.permissions =
			static_cast<domain::ResourcePermissions>(sri.permissions | domain::readable);
	if (fileSystem::isWritable(sri.resourcePath))
		sri.permissions =
			static_cast<domain::ResourcePermissions>(sri.permissions | domain::writable);
	if (fileSystem::isExecutable(sri.resourcePath))
		sri.permissions =
			static_cast<domain::ResourcePermissions>(sri.permissions | domain::executable);

	sri.contentLength = fileSystem::getSize(sri.resourcePath);

	sri.canBeDeleted = fileSystem::isDeletable(sri.resourcePath);

	return sri;
}

// get
app::SystemResourceInfos
Server::locate(std::string const &id, std::string const &locPath, std::string const &rootPath) const
{
	app::SystemResourceInfos sri;

	sri = setSRI(resolvePhysicalPath(id, locPath, rootPath));
	return sri;
}

app::SystemResourceInfos Server::locateDefaultIndex(
	std::vector<std::string> const &indexesId,
	std::string const			   &locPath,
	std::string const			   &rootPath
) const
{
	std::string resPath = resolvePhysicalPath("/", locPath, rootPath);

	if (indexesId.empty())
		throw("banana, no index"); // TODO: check if throw

	std::vector<std::string>::const_iterator ite = indexesId.end();
	std::vector<std::string>::const_iterator it = indexesId.begin();
	for (; it != ite; ++it)
	{
		if (fileSystem::exists(resPath + *it) && fileSystem::isRegularFile(resPath + *it))
		{
			return setSRI(resPath + *it);
		}
	}
	return setSRI(resPath + indexesId[0]);
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
