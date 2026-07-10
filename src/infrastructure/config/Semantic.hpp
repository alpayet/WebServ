#ifndef SEMANTIC_HPP
# define SEMANTIC_HPP

# include "infrastructure/config/Config.hpp"
# include <string>

class SemanticException : public ConfigException
{
	public:
		SemanticException(const std::string& msg) throw() : ConfigException("Error\n" + msg) {};
};

#include "infrastructure/config/Parser.hpp"
void 	checkDupLoc(p_ServerConfig s);
void 	checkDupHostname(p_Config c);
void	initServerConfig(ServerConfig& s, p_ServerConfig ps);
void	initLocation(ServerConfig& s, p_ServerConfig ps);


#endif
