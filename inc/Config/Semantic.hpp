#ifndef SEMANTIC_HPP
# define SEMANTIC_HPP

// class Semantic
// {
	
// };

# include <exception>
# include <string>

class SemanticException : std::exception
{
	protected:
		std::string m_msg;

};

#include "Config/Parser.hpp"
bool	checkOverlap(p_Config c);
bool	checkDupLoc(p_Server s);

#endif
