#include "infrastructure/config/Semantic.hpp"
#include "infrastructure/config/Parser.hpp"
#include <iterator>
#include <sstream>
#include <vector>

void initLocation(ServerConfig &s, p_ServerConfig ps)
{
	if (ps.locations.empty())
		return;

	std::vector<p_Location>::const_iterator l_ite = ps.locations.end();
	for (std::vector<p_Location>::const_iterator l_it = ps.locations.begin(); l_it != l_ite;
		 *l_it++)
	{
		Location loc;

		if (l_it->path[0] != '/' || l_it->path[l_it->path.size() - 1] != '/')
			throw SemanticException(
				"location path should be a directory from absolute path (so start and end with "
				"'/')"
			);
		loc.path = l_it->path;

		loc.met_get = true;
		loc.met_post = true;
		loc.met_del = true;

		loc.autoindex = false;

		std::vector<p_Directive>::const_iterator ite = l_it->directives.end();
		for (std::vector<p_Directive>::const_iterator it = l_it->directives.begin(); it != ite;
			 *it++)
		{
			if (it->name == "root")
			{
				if (it->values[0][0] != '/' || it->values[0][it->values[0].size() - 1] != '/')
					throw SemanticException(
						"`root` should be a directory from absolute path (so start and end with "
						"'/')"
					);
				loc.root = it->values[0];
			}
			else if (it->name == "index")
			{
				for (size_t i = 0; i < it->values.size(); ++i)
				{
					if (it->values[i].find("/") != std::string::npos)
						throw SemanticException("`index` should just be a file, not a path to one");
					loc.index.push_back(it->values[i]);
				}
			}
			else if (it->name == "cgi")
			{
				loc.cgi.push_back(it->values[0]);
			}
			else if (it->name == "limit_except")
			{
				loc.met_get = false;
				loc.met_post = false;
				loc.met_del = false;

				for (size_t i = 0; i < it->values.size(); ++i)
				{
					if (it->values[i] == "GET")
						loc.met_get = true;
					else if (it->values[i] == "POST")
						loc.met_post = true;
					else if (it->values[i] == "DEL")
						loc.met_del = true;
					else
					{
						throw SemanticException(
							"Methods '" + it->values[i] + "' in 'limit_except' doesn't exist"
						);
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
				std::istringstream iss(it->values[0]);
				int				   ret;
				iss >> ret;
				if (ret < 100 || ret > 599 || !iss.eof())
				{
					throw SemanticException("Not a valid error page number");
				}
				loc.ret = ret;
			}
		}
		s.addLocation(loc);
	}
}

void initServerConfig(ServerConfig &s, p_ServerConfig ps)
{
	if (ps.directives.empty())
	{
		throw SemanticException("A server must have a root");
	}

	std::vector<p_Directive>::const_iterator ite = ps.directives.end();
	for (std::vector<p_Directive>::const_iterator it = ps.directives.begin(); it != ite; *it++)
	{
		if (it->name == "listen")
		{
			std::istringstream iss(it->values[0]);
			int				   port;
			iss >> port;
			if (port < 1024 || port > 65535 || !iss.eof())
			{
				throw SemanticException("Listen doesnt have a valid port number");
			}
			s.setPort(port);
		}
		else if (it->name == "hostname")
		{
			s.setHostname(it->values[0]);
		}
		else if (it->name == "error_page")
		{
			std::istringstream iss(it->values[0]);
			int				   ret;
			iss >> ret;
			if (ret < 100 || ret > 599)
			{
				throw SemanticException("Not a valid error page number");
			}
			s.addErrPage(ret, it->values[1]);
		}
		else if (it->name == "client_max_body_size")
		{
			if (it->values[0].find("-") != std::string::npos)
			{
				throw SemanticException("Client body size can't be negative");
			}
			std::istringstream iss(it->values[0]);
			std::size_t		   size;
			iss >> size;
			if (!iss.eof())
			{
				throw SemanticException("Client body size can't have non-digit value");
			}
			s.setClientMaxBody(size);
		}
		else if (it->name == "root")
		{
			if (it->values[0][0] != '/' || it->values[0][it->values[0].size() - 1] != '/')
				throw SemanticException(
					"`root` should be a directory from absolute path (so start and end with "
					"'/')"
				);
			s.setRoot(it->values[0]);
		}
		else if (it->name == "index")
		{
			for (size_t i = 0; i < it->values.size(); ++i)
			{
				if (it->values[i].find("/") != std::string::npos)
					throw SemanticException("`index` should just be a file, not a path to one");
				s.addIndex(it->values[i]);
			}
		}
	}
	if (s.getRoot().empty())
	{
		throw SemanticException("A server must have a root");
	}
	if (s.getHostname().empty())
	{
		throw SemanticException("A server must have an hostname");
	}
}

void checkDupLoc(p_ServerConfig s)
{
	size_t nb_locs = s.locations.size();
	if (nb_locs == 0)
		return;
	std::string path1, path2;

	for (size_t i = 0; i < nb_locs - 1; ++i)
	{
		path1 = s.locations[i].path;
		for (size_t j = i + 1; j < nb_locs; ++j)
		{
			path2 = s.locations[j].path;
			if (path1 == path2)
			{
				throw SemanticException("Multiple location blocks with the same path");
			}
		}
	}
}

void checkDupHostname(p_Config c)
{
	size_t nb_servers = c.servers.size();
	if (nb_servers < 2)
		return;
	std::string port1 = "8080", port2 = "8080";
	std::string host1, host2;

	for (size_t i = 0; i < nb_servers - 1; ++i)
	{
		std::vector<p_Directive>::const_iterator d_ite = c.servers[i].directives.end();
		for (std::vector<p_Directive>::const_iterator d_it = c.servers[i].directives.begin();
			 d_it != d_ite; *d_it++)
		{
			if (d_it->name == "hostname")
			{
				host1 = d_it->values[0];
			}
			if (d_it->name == "listen")
			{
				port1 = d_it->values[0];
			}
		}
		for (size_t j = i + 1; j < nb_servers; ++j)
		{
			std::vector<p_Directive>::const_iterator d_ite2 = c.servers[j].directives.end();
			for (std::vector<p_Directive>::const_iterator d_it2 = c.servers[j].directives.begin();
				 d_it2 != d_ite2; *d_it2++)
			{
				if (d_it2->name == "hostname")
				{
					host2 = d_it2->values[0];
				}
				if (d_it2->name == "listen")
				{
					port2 = d_it2->values[0];
				}
			}
			if (port1 == port2)
			{
				if (host1 == host2)
				{
					throw SemanticException("Same couple hostname:port for different servers");
				}
			}
		}
	}
}