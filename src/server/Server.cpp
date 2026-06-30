
#include "server/Server.hpp"

#include <cerrno>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

#include "application/Exception.hpp"
#include "config/Semantic.hpp"
#include "infrastructure/http/router/RoutePolicy.hpp"
#include "infrastructure/storage/file_system/Storage.hpp"

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
	route.matchedRoute = loc.path;
	if (!loc.root.empty())
		route.rootPath = loc.root;
	else
		route.rootPath = m_root + loc.path.substr(1, loc.path.size() - 1);
	route.isListingEnabled = loc.autoindex;
	if (!loc.index.empty())
		route.indexesId = loc.index;
	else
		route.indexesId = m_index;
	route.allowedMethods = getAllowedMethods(loc);
	return route;
}

// TODO: check
std::string Server::resolvePhysicalPath(
	std::string const &uri, std::string const &matchedRoute, std::string const &rootPath
) const
{
	// std::string path;
	// if (rootPath.empty())
	// 	path = m_root + matchedRoute.substr(1, matchedRoute.size() - 1);
	// else
	// 	path = rootPath;
	// std::string resUri = uri;
	// resUri.replace(0, matchedRoute.size(), path);
	// return resUri;

	std::string resUri = uri;
	resUri.replace(0, matchedRoute.size(), rootPath);

	char resPath[PATH_MAX];
	if (!realpath(resUri.c_str(), resPath))
	{
		if (errno == EIO || errno == ENOMEM)
			throw std::runtime_error("realpath");
	}
	resUri = resPath;
	if (resUri.find(rootPath) != 0)
		throw app::Exception(app::Exception::traversalPath);
	return resUri;
}

app::SystemResourceInfo setSRI(std::string const &path)
{
	app::SystemResourceInfo sri;

	sri.resourcePath = path;

	if (!fileSystem::Storage::exists(sri.resourcePath))
	{
		sri.exists = false;
		return sri;
	}
	sri.exists = true;

	if (fileSystem::Storage::isRegularFile(sri.resourcePath))
		sri.type = domain::leaf;
	else if (fileSystem::Storage::isDirectory(sri.resourcePath))
		sri.type = domain::collection;
	else
		sri.type = domain::unknown;

	sri.permissions = domain::none;
	if (fileSystem::Storage::isReadable(sri.resourcePath))
		sri.permissions =
			static_cast<domain::ResourcePermissions>(sri.permissions | domain::readable);
	if (fileSystem::Storage::isWritable(sri.resourcePath))
		sri.permissions =
			static_cast<domain::ResourcePermissions>(sri.permissions | domain::writable);
	if (fileSystem::Storage::isExecutable(sri.resourcePath))
		sri.permissions =
			static_cast<domain::ResourcePermissions>(sri.permissions | domain::executable);

	sri.resourceSize = fileSystem::Storage::getSize(sri.resourcePath);

	sri.canBeDeleted = fileSystem::Storage::isDeletable(sri.resourcePath);

	return sri;
}

// get
app::SystemResourceInfo Server::locate(
	std::string const &id, std::string const &matchedRoute, std::string const &rootPath
) const
{
	app::SystemResourceInfo sri;

	sri = setSRI(resolvePhysicalPath(id, matchedRoute, rootPath));
	return sri;
}

// TODO: check directory before calling
app::SystemResourceInfo Server::locateDefaultIndex(
	std::vector<std::string> const &indexesId,
	std::string const			   &matchedRoute,
	std::string const			   &rootPath
) const
{
	std::string resPath = resolvePhysicalPath("/", matchedRoute, rootPath);
	if (resPath.back() != '/')
		resPath += "/";

	if (indexesId.empty())
		return app::SystemResourceInfo();

	std::vector<std::string>::const_iterator ite = indexesId.end();
	std::vector<std::string>::const_iterator it = indexesId.begin();
	for (; it != ite; ++it)
	{
		if (fileSystem::Storage::exists(resPath + *it) &&
			fileSystem::Storage::isRegularFile(resPath + *it))
		{
			return setSRI(resPath + *it);
		}
	}
	return setSRI(resPath + indexesId[0]);
}

std::string Server::getHttpVersion(void) const { return ("HTTP/1.0"); }

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

Server::TransportProtocol Server::getTransportProtocol(void) const { return m_transport; }

Server::ApplicativeProtocol Server::getApplicativeProtocol(void) const
{
	return m_applicative_protocol;
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
