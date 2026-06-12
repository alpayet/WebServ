
#include "server/Server.hpp"
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

#include "config/Semantic.hpp"

std::ostream &operator<<(std::ostream &os, const Location &l)
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

std::ostream &operator<<(std::ostream &os, const Server &s)
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

Location Server::findLocationFromUri(std::string const &uri) const
{
	std::size_t pos = uri.find_last_of('/');
	std::string dir_path;
	if (pos == std::string::npos)
		dir_path = uri;
	else
		dir_path = uri.substr(0, pos);

	std::vector<Location>::const_iterator ite = this->m_locations.end();
	for (std::vector<Location>::const_iterator it = this->m_locations.begin(); it != ite; ++it)
	{
		std::string cmp;
		if (!it->path.empty())
			cmp = it->path;
		// else
		// 	cmp = this->m_root;
		// TODO: check if need the else
		if (cmp == dir_path)
			return *it;
	}
	throw("banana");
}

// TODO: get root from path - file and append file to root
std::string Server::resolvePhysicalPath(std::string const &uri) const
{
	Location loc = findLocationFromUri(uri);
	// if (loc == 0)
	// {
	// 	throw("could resolve physical path");
	// }
	std::string phy_path;
	if (!loc.root.empty())
		phy_path = loc.root;
	else
		phy_path = m_root + loc.path;

	std::size_t pos = uri.find_last_of('/');
	if (pos != std::string::npos)
		phy_path += uri.substr(pos, uri.size() - pos);

	return phy_path;
}

std::vector<std::string> Server::getAllowedMethods(std::string const &uri) const
{
	Location loc = findLocationFromUri(uri);
	// if (loc == 0)
	// 	throw("couldnt fetch allowed methods");
	std::vector<std::string> methods;
	if (loc.met_get)
		methods.push_back("GET");
	if (loc.met_post)
		methods.push_back("POST");
	if (loc.met_del)
		methods.push_back("DELETE");
	return (methods);
}

std::size_t Server::getMaxBodySize() const { return (m_max_body); }
// void param
