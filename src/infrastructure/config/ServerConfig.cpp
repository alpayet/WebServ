
#include "infrastructure/config/ServerConfig.hpp"

#include <algorithm>
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
#include "infrastructure/config/Semantic.hpp"
#include "infrastructure/server/application_protocol/http/exceptions/Exception.hpp"
#include "infrastructure/server/application_protocol/http/methods.hpp"
#include "infrastructure/server/application_protocol/http/router/RoutePolicy.hpp"
#include "infrastructure/storage/file_system/fileSystem.hpp"

namespace webserv {
Location ServerConfig::findLocationFromUri(std::string const &uri) const
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

	Location loc;
	loc.index = m_index;
	loc.root = m_root;
	return (loc);
}

std::vector<std::string> ServerConfig::getAllowedMethods(Location const &loc) const
{
	std::vector<std::string> methods;
	if (loc.met_get)
		methods.push_back(http::GET);
	if (loc.met_post)
		methods.push_back(http::POST);
	if (loc.met_del)
		methods.push_back(http::DELETE);
	return (methods);
}

http::RoutePolicy ServerConfig::match(std::string const &uri) const
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
	route.hasReturn = loc.ret != 0;
	route.returnCode = loc.ret;
	std::size_t pos = uri.find_last_of("/");
	if (pos != std::string::npos)
	{
		std::string file = uri.substr(pos + 1, uri.size() - pos + 1);
		if (std::find(loc.cgi.begin(), loc.cgi.end(), file) != loc.cgi.end())
			route.isCgi = true;
		else
			route.isCgi = false;
	}
	else
	{
		route.isCgi = false;
	}

	return route;
}

std::string ServerConfig::resolvePhysicalPath(
	std::string const &uri, std::string const &matchedRoute, std::string const &rootPath
) const
{
	std::string resUri = uri;
	resUri.replace(0, matchedRoute.size(), rootPath);

	char resPath[PATH_MAX];
	if (!realpath(resUri.c_str(), resPath))
	{
		if (errno == EIO || errno == ENOMEM)
			throw std::runtime_error("realpath");
	}
	if (resUri[resUri.size() - 1] == '/')
	{
		resUri = resPath;
		resUri += "/";
	}
	else
		resUri = resPath;
	if (resUri.find(rootPath) != 0)
		throw app::Exception(app::Exception::PATH_TRAVERSAL_DETECTED);
	return resUri;
}

std::string ServerConfig::resolvePhysicalPath(std::string const &uri) const
{
	std::string resUri = uri;
	resUri.replace(0, 1, m_root);

	return resUri;
}

app::SystemResourceInfo setSRI(std::string const &path)
{
	app::SystemResourceInfo sri;

	sri.resourcePath = path;

	if (!fileSystem::exists(sri.resourcePath))
	{
		sri.exists = false;
		return sri;
	}
	sri.exists = true;

	if (fileSystem::isRegularFile(sri.resourcePath))
		sri.type = domain::LEAF;
	else if (fileSystem::isDirectory(sri.resourcePath))
		sri.type = domain::COLLECTION;
	else
		sri.type = domain::UNKNOWN;

	sri.permissions = domain::NONE;
	if (fileSystem::isReadable(sri.resourcePath))
		sri.permissions =
			static_cast<domain::ResourcePermissions>(sri.permissions | domain::READABLE);
	if (fileSystem::isWritable(sri.resourcePath))
		sri.permissions =
			static_cast<domain::ResourcePermissions>(sri.permissions | domain::WRITABLE);
	if (fileSystem::isExecutable(sri.resourcePath))
		sri.permissions =
			static_cast<domain::ResourcePermissions>(sri.permissions | domain::EXECUTABLE);

	sri.resourceSize = fileSystem::getSize(sri.resourcePath);

	sri.canBeDeleted = fileSystem::isDeletable(sri.resourcePath);

	return sri;
}

app::SystemResourceInfo ServerConfig::locate(
	std::string const &id, std::string const &matchedRoute, std::string const &rootPath
) const
{
	app::SystemResourceInfo sri;

	sri = setSRI(resolvePhysicalPath(id, matchedRoute, rootPath));
	return sri;
}

app::SystemResourceInfo ServerConfig::locateDefaultIndex(
	std::vector<std::string> const &indexesId,
	std::string const			   &matchedRoute,
	std::string const			   &rootPath
) const
{
	std::string resPath = resolvePhysicalPath("/", matchedRoute, rootPath);
	if (resPath[resPath.size() - 1] != '/')
		resPath += "/";

	if (indexesId.empty())
		return app::SystemResourceInfo();

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

app::SystemResourceInfo ServerConfig::locateErrorPage(std::string const &uri) const
{
	app::SystemResourceInfo sri;

	sri = setSRI(resolvePhysicalPath(uri));
	return sri;
}

std::string ServerConfig::getHttpVersion(void) const { return ("HTTP/1.1"); }

bool ServerConfig::isSupportedHttpVersion(std::string const &version) const
{
	return (version == "HTTP/1.1" || version == "HTTP/1.0");
}

std::size_t ServerConfig::getMaxRequestLineSize(void) const { return 8192; }

std::size_t ServerConfig::getMaxHeaderLineSize(void) const { return 8192; }

std::size_t ServerConfig::getMaxHeaderCount(void) const { return 100; }

std::size_t ServerConfig::getMaxBodySize(void) const { return (m_max_body); }

std::size_t ServerConfig::getMaxBodySize(std::string const &uri) const
{
	static_cast<void>(uri);
	return (m_max_body);
}

ServerConfig::TransportProtocol ServerConfig::getTransportProtocol(void) const
{
	return m_transport;
}

ServerConfig::ApplicativeProtocol ServerConfig::getApplicativeProtocol(void) const
{
	return m_application_protocol;
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

std::ostream &operator<<(std::ostream &os, ServerConfig const &s)
{
	os << "***SERVER***" << std::endl;

	os << "\tHostname: " << s.getHostname() << std::endl;
	os << "\tPort: " << s.getPort() << std::endl;
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
} // namespace webserv
