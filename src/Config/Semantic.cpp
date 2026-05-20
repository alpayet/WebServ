#include "Config/Semantic.hpp"
// #include "Server/Server.hpp"
#include "Config/Parser.hpp"
#include <vector>
#include <iterator>
#include <string>
#include <iostream>

#include "Config/keywords.h"
#include "Server/Server.hpp"
#include <sstream>

// TODO: check if enough instructions in file
/**
 * server -> need at least 1
 * listen -> might default to 80
 * location -> path always start with '/'
 * root -> maybe force no end '/'
 * interface -> maybe be multi instead of uniq
 * 
 */

bool	initServer(Server s, p_Server ps)
{
	std::vector<p_Location>::const_iterator l_ite = ps.locations.end();
	for (std::vector<p_Location>::const_iterator l_it = ps.locations.begin() ; l_it != l_ite ; *l_it++)
	{
		Location loc;

		loc.path = l_it->path;

		loc.met_get = true;
		loc.met_post = true;
		loc.met_del = true;

		loc.autoindex = false;

		std::vector<p_Directive>::const_iterator ite = l_it->directives.end();
		for (std::vector<p_Directive>::const_iterator it = l_it->directives.begin() ; it != ite ; *it++)
		{
			if (it->name == "root")
			{
				loc.root = it->values[0];
			}
			else if (it->name == "index")
			{
				loc.index = it->values[0];
			}
			else if (it->name == "proxy_pass")
			{
				loc.cgi = it->values[0];
			}
			else if (it->name == "limit_except")
			{
				loc.met_get = false;
				loc.met_post = false;
				loc.met_del = false;

				for (size_t i = 0 ; i < it->values.size() ; ++i)
				{
					if (it->values[i] == "GET")
						loc.met_get = true;
					else if (it->values[i] == "POST")
						loc.met_post = true;
					else if (it->values[i] == "DEL")
						loc.met_del = true;
					else
					{
						std::cerr << "Error\nMethods in limit_except doesn't exist" << std::endl;
						return false;
					}
				}
			}
			else if (it->name == "autoindex")
			{
				if (it->values[0].tolower() == "on")
					loc.autoindex = true;
				else if (it->values[0].tolower() == "off")
					loc.autoindex = false;
				else
				{
					std::cerr << "Error\nAutoindex should be 'on' or 'off'" << std::endl;
					return false;
				}
			}
			else if (it->name == "return")
			{
				std::istringstream	iss(it->values[0]);
				int		ret;
				iss >> ret;
				if (ret < 100 || ret > 599)
				{
					std::cerr << "Error\nNot a valid error page number" << std::endl;
					return false;
				}
				loc.ret = ret;
			}
		}
		s.addLocation(loc);
	}

	return true;
}

// TODO: check if keyword already exist and append
bool	initServer(Server s, p_Server ps)
{
	std::vector<p_Directive>::const_iterator ite = ps.directives.end();
	for (std::vector<p_Directive>::const_iterator it = ps.directives.begin() ; it != ite ; *it++)
	{
		if (it->name == "listen")
		{
			std::istringstream	iss(it->values[0]);
			int	port;
			iss >> port;
			if (port < 1024 || port > 65535)
			{
				std::cerr << "Error\nListen doesnt have a valid port number" << std::endl;
				return false;
			}
			s.setPort(port);
		}
		else if (it->name == "interface")
		{
			std::istringstream	iss(it->values[0]);
			int		nb;
			char	del;
			for (int i = 0 ; i < 3 ; ++i)
			{
				iss >> nb;
				iss >> del;
				if (nb < 0 || nb > 255 || del != '.')
				{
					std::cerr << "Error\nInterface IP wrongly formatted" << std::endl;
					return false;
				}
			}
			iss >> nb;
			iss >> del;
			if (nb < 0 || nb > 255 || del != 0)
			{
				std::cerr << "Error\nInterface IP wrongly formatted" << std::endl;
				return false;
			}
			s.setInterface(it->values[0]);
		}
		else if (it->name == "error_page")
		{
			std::istringstream	iss(it->values[0]);
			int		ret;
			iss >> ret;
			if (ret < 100 || ret > 599)
			{
				std::cerr << "Error\nNot a valid error page number" << std::endl;
				return false;
			}
			s.addErrPage(ret, it->values[1]);
		}
		else if (it->name == "client_max_body_size")
		{
			std::istringstream	iss(it->values[0]);
			long		size;
			iss >> size;
			if (size < 0 )
			{
				std::cerr << "Error\nClient body size can't be negative" << std::endl;
				return false;
			}
			s.setClientMaxBody(size);
		}
		else if (it->name == "root")
		{
			s.setRoot(it->values[0]);
		}
		else if (it->name == "index")
		{
			s.setIndex(it->values[0]);
		}
	}

	return true;
}

// TODO: check if those who need number are indeed numbers

bool	checkDupLoc(p_Server s)
{
	size_t	nb_locs = s.locations.size();
	std::string	path1, path2;

	for (size_t i = 0 ; i < nb_locs - 1 ; ++i)
	{
		path1 = s.locations[i].path;
		for (size_t j = i + 1 ; j < nb_locs ; ++j)
		{
			path2 = s.locations[j].path;
			if (path1 == path2)
			{
				std::cerr << "Error\nMultiple location blocks with the same path" << std::endl;
				return false;
			}
		}
	}
	return true;
}

bool	checkOverlap(p_Config c)
{
	size_t	nb_servers = c.servers.size();
	std::string	port1, port2;
	std::string	ip1, ip2;

	for (size_t i = 0 ; i < nb_servers - 1 ; ++i)
	{
		std::vector<p_Directive>::const_iterator d_ite = c.servers[i].directives.end();
		for (std::vector<p_Directive>::const_iterator d_it = c.servers[i].directives.begin() ; d_it != d_ite ; *d_it++)
		{
			if (d_it->name == "listen")
			{
				port1 = d_it->values[0];
			}
			if (d_it->name == "interface")
			{
				ip1 = d_it->values[0];
			}
		}
		for (size_t j = i + 1 ; j < nb_servers ; ++j)
		{
			std::vector<p_Directive>::const_iterator d_ite2 = c.servers[j].directives.end();
			for (std::vector<p_Directive>::const_iterator d_it2 = c.servers[j].directives.begin() ; d_it2 != d_ite2 ; *d_it2++)
			{
				if (d_it2->name == "listen")
				{
					port2 = d_it2->values[0];
				}
				if (d_it2->name == "interface")
				{
					ip2 = d_it2->values[0];
				}
			}
			if (port1 == port2)
			{
				if (ip1 == ip2)
				{
					std::cerr << "Error\nSame couple interface:port for different servers" << std::endl;
					return false;
				}
				if (ip1 == "0.0.0.0" || ip2 == "0.0.0.0")
				{
					std::cerr << "Error\nOverlapping of IP addresses with same port for different servers" << std::endl;
					return false;
				}
			}
		}
	}
	return true;
}

