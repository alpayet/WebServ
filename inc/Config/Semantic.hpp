#ifndef SEMANTIC_HPP
# define SEMANTIC_HPP

// class Semantic
// {
	
// };

# include "Config/Config.hpp"
# include <string>

// class ConfigException;

class SemanticException : public ConfigException
{
	public:
		SemanticException(const std::string& msg) throw() : ConfigException("Error\n" + msg) {};
};

#include "Config/Parser.hpp"
void	checkOverlap(p_Config c);
void	checkDupLoc(p_Server s);
void	initServer(Server& s, p_Server ps);
void	initLocation(Server& s, p_Server ps);


#endif
