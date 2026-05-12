#include "Config/Semantic.hpp"

// TODO: check if enough instructions in file
/**
 * server -> need at least 1
 * listen -> might default to 80
 * 
 */

// TODO: check if keyword already exist and append

// TODO: check duplicates

// TODO: check if those who need number are indeed numbers

// TODO: check overlap (same port, differents ips, no 0.0.0.0)
// #include "Server/Server.hpp"
#include "Config/Parser.hpp"
#include <vector>
#include <iterator>
#include <string>
#include <iostream>
bool checkOverlap(p_Config c)
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

