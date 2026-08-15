#ifndef SEMANTIC_HPP
#define SEMANTIC_HPP

#include "infrastructure/config/Config.hpp"
#include "infrastructure/config/Parser.hpp"
#include <string>

namespace webserv {
class SemanticException : public ConfigException
{
  public:
	SemanticException(std::string const &msg) throw() : ConfigException("Error\n" + msg) {};
};

void checkDupLoc(p_ServerConfig s);
void checkDupHostname(p_Config c);
void initServerConfig(ServerConfig &s, p_ServerConfig ps);
void initLocation(ServerConfig &s, p_ServerConfig ps);
} // namespace webserv

#endif
