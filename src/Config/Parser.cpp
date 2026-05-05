#include "Config/Parser.hpp"
#include <iostream>

/** CONSTRUCTORS */
Parser::Parser(const std::vector<Token>& tokens): m_tokens(tokens)
{
	// TODO: deep copy
	m_it = m_tokens.begin();
	m_ite = m_tokens.end();
}

Parser::Parser(Parser& other) : m_tokens(other.m_tokens)
{
	m_it = m_tokens.begin();
	m_ite	= m_tokens.end();
}

Parser::~Parser()
{

}

bool	Parser::expect(char c)
{
	if ((m_it->type == char_lbracket && c == '{')
		|| (m_it->type == char_rbracket && c == '}')
		|| (m_it->type == char_end && c == ';'))
		return true;
	std::cerr << "Error\nWrongly formatted file, expected a '" << c
			<< "' instead of '" << m_it->data[0] << "'" << std::endl;
	return false;
}

/** FUNCTIONS */

// TODO: check if enough instructions in file
// bool	Parser::checkNecessary()
// {

// 	return true;
// }

// TODO: check if those who need number are indeed numbers
// TODO: check duplicates
// TODO: check if keyword already exist and append
bool	Parser::parseDirective(Server& serv)
{
	// TODO: switch case for serv instruction
	Directive direc;

	if (m_it->type != res_word)
	{
		std::cerr << "Error\nWrongly formatted file, expected a directive name" << m_it->data << std::endl;
		return false;
	}
	direc.name = m_it->data;
	*m_it++;
	for ( ; m_it->type == str_type || m_it->type == int_type ; *m_it++)
	{
		direc.values.push_back(m_it->data);
	}
	if (!expect(';'))
	{
		return false;
	}
	*m_it++;
	serv.directives.push_back(direc);
	return true;

}

// TODO: check if those who need number are indeed numbers
// TODO: check duplicates
bool	Parser::parseDirective(Location& location)
{
	// TODO: switch case for loc instruction
	Directive direc;

	if (m_it->type != res_word)
	{
		std::cerr << "Error\nWrongly formatted file, expected a directive name " << m_it->data << std::endl;
		return false;
	}
	direc.name = m_it->data;
	*m_it++;
	for ( ; m_it->type == str_type || m_it->type == int_type ; *m_it++)
	{
		direc.values.push_back(m_it->data);
	}
	if (!expect(';'))
	{
		return false;
	}
	*m_it++;
	location.directives.push_back(direc);
	return true;
}

bool	Parser::parseLocation(Server& serv)
{
	*m_it++;
	if (m_it->type != str_type)
	{
		std::cerr << "Error\nWrongly formatted file, expected a directory for the location block" << std::endl;
		return false;
	}

	Location loc;
	loc.path = m_it->data;
	*m_it++;
	if (!expect('{'))
	{
		return false;
	}	
	*m_it++;
	while (m_it != m_ite && m_it->type != char_rbracket)
	{
		if (m_it->type == res_word && m_it->data == "location")
		{
			std::cerr << "Error\nLocation block can't contain another location block" << std::endl;
			return false;
		}

		if (!parseDirective(loc))
		{
			return false;
		}
	}
	if (!expect('}'))
		return false;
	*m_it++;
	serv.locations.push_back(loc);
	return true;
}

bool	Parser::parseServer()
{
	*m_it++;
	if (!expect('{'))
		return false;
	
	*m_it++;

	Server serv;

	while (m_it != m_ite && m_it->type != char_rbracket)
	{
		if (m_it->type == res_word && m_it->data == "server")
		{
			std::cerr << "Error\nServer block can't contain another server block" << std::endl;
			return false;
		}
		if (m_it->type == res_word && m_it->data == "location")
		{
			if (!parseLocation(serv))
			{
				return false;
			}
		}
		else
		{
			if (!parseDirective(serv))
			{
				return false;
			}
		}
	}
	if (!expect('}'))
		return false;
	*m_it++;
	m_config.servers.push_back(serv);
	return true;
}

bool	Parser::parseConfig()
{
	while (m_it != m_ite)
	{
		if	(m_it->type == res_word && m_it->data == "server")
		{
			if (!parseServer())
			{
				return false;
			}
		}
	}
	return true;
}

bool	Parser::parse(Config& config)
{
	if (!parseConfig())
	{
		return false;
	}
	// TODO: probably deep copy too
	config = m_config;
	return true;
}

std::ostream& operator<<(std::ostream& os, const Config& c)
{
	std::vector<Server>::const_iterator s_ite = c.servers.end();
	for (std::vector<Server>::const_iterator s_it = c.servers.begin() ; s_it != s_ite ; *s_it++)
	{
		os << "***SERVER***" << std::endl;
		std::vector<Location>::const_iterator l_ite = s_it->locations.end();
		for (std::vector<Location>::const_iterator l_it = s_it->locations.begin() ; l_it != l_ite ; *l_it++)
		{
			os << "\t***LOCATION***" << std::endl;
			os << "\tPath: " << l_it->path << std::endl;
			std::vector<Directive>::const_iterator d_ite = l_it->directives.end();
			for (std::vector<Directive>::const_iterator d_it = l_it->directives.begin() ; d_it != d_ite ; *d_it++)
			{
				os << "\t\t***DIRECTIVE***" << std::endl;
				os << "\t\tName: " << d_it->name << std::endl;
				std::vector<std::string>::const_iterator str_ite = d_it->values.end();
				for (std::vector<std::string>::const_iterator str_it = d_it->values.begin() ; str_it != str_ite ; *str_it++)
				{
					os << "\t\tValues: " << *str_it << " ";
				}
				os << ";" << std::endl;
				os << "\t\t**ENDDIRECTIVE**" << std::endl;
			}
			os << "\t**ENDLOCATION**" << std::endl;
		}
		std::vector<Directive>::const_iterator d_ite = s_it->directives.end();
		for (std::vector<Directive>::const_iterator d_it = s_it->directives.begin() ; d_it != d_ite ; *d_it++)
		{
			os << "\t***DIRECTIVE***" << std::endl;
			os << "\tName: " << d_it->name << std::endl;
			std::vector<std::string>::const_iterator str_ite = d_it->values.end();
			for (std::vector<std::string>::const_iterator str_it = d_it->values.begin() ; str_it != str_ite ; *str_it++)
			{
				os << "\tValues: " << *str_it << " ";
			}
			os << ";" << std::endl;
			os << "\t**ENDDIRECTIVE**" << std::endl;
		}
		os << "**ENDSERVER**" << std::endl;
	}
	return os;
}
