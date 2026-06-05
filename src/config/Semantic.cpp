#include "config/Semantic.hpp"
#include "config/Parser.hpp"
#include <vector>
#include <iterator>
#include <sstream>

// TODO: check location end with '/'
// TODO: end root with '/'
void	initLocation(Server& s, p_Server ps)
{
	if (ps.locations.empty())
		return ;

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
				for (size_t i = 0 ; i < it->values.size() ; ++i)
				{
					loc.index.push_back(it->values[i]);
				}
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
						throw SemanticException("Methods '" + it->values[i] + "' in 'limit_except' doesn't exist");
					}
				}
			}
			else if (it->name == "autoindex")
			{
				if (it->values[0] == "on")
					loc.autoindex = true;
				else if (it->values[0] == "off")
					loc.autoindex = false;
				else
				{
					throw SemanticException("Autoindex should be 'on' or 'off'");
				}
			}
			else if (it->name == "return")
			{
				std::istringstream	iss(it->values[0]);
				int		ret;
				iss >> ret;
				if (ret < 100 || ret > 599)
				{
					throw SemanticException ("Not a valid error page number");
				}
				loc.ret = ret;
			}
		}
		s.addLocation(loc);
	}
}
#include <iostream>
void	initServer(Server& s, p_Server ps)
{
	if (ps.directives.empty())
	{
		throw SemanticException ("A server must have a root");
	}

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
				throw SemanticException ("Listen doesnt have a valid port number");
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
					throw SemanticException ("Interface IP wrongly formatted");
				}
			}
			iss >> nb;
			if (nb < 0 || nb > 255 || !iss.eof())
			{
				throw SemanticException ("Interface IP wrongly formatted = ");
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
				throw SemanticException ("Not a valid error page number");
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
				throw SemanticException ("Client body size can't be negative");
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
	if (s.getRoot().empty())
	{
		throw SemanticException ("A server must have a root");
	}
}

void	checkDupLoc(p_Server s)
{
	size_t	nb_locs = s.locations.size();
	if (nb_locs == 0)
		return ;
	std::string	path1, path2;

	for (size_t i = 0 ; i < nb_locs - 1 ; ++i)
	{
		path1 = s.locations[i].path;
		for (size_t j = i + 1 ; j < nb_locs ; ++j)
		{
			path2 = s.locations[j].path;
			if (path1 == path2)
			{
				throw SemanticException ("Multiple location blocks with the same path");
			}
		}
	}
}

void	checkOverlap(p_Config c)
{
	size_t	nb_servers = c.servers.size();
	if (nb_servers < 2)
		return ;
	std::string	port1 = "8080", port2 = "8080";
	std::string	ip1 = "0.0.0.0", ip2 = "0.0.0.0";

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
					throw SemanticException ("Same couple interface:port for different servers");
				}
				if (ip1 == "0.0.0.0" || ip2 == "0.0.0.0")
				{
					throw SemanticException ("Overlapping of IP addresses with same port for different servers");
				}
			}
		}
	}
}

