#include "config/Parser.hpp"
#include "config/keywords.h"
#include <iostream>
#include <sstream>

Parser::Parser(const std::vector<Token> &tokens) : m_tokens(tokens)
{
	m_it = m_tokens.begin();
	m_ite = m_tokens.end();
}

void Parser::expect(char c)
{
	if (m_it == m_ite)
		throw ParserFormatException("unexpected end of file");
	if ((m_it->type == char_lbracket && c == '{') || (m_it->type == char_rbracket && c == '}') ||
		(m_it->type == char_end && c == ';'))
		return;
	std::ostringstream os;
	if (m_it->type == 0)
		os << "expected a '" << c << "' instead of end of file";
	else
		os << "expected a '" << c << "' instead of '" << m_it->data[0] << "'";
	throw ParserFormatException(os.str());
}

template <typename T> p_Directive Parser::parseDirective(T &t, e_block comp)
{
	p_Directive direc;

	if (m_it->type != res_word)
	{
		std::ostringstream os;
		os << "expected a directive name, not " << m_it->data;
		throw ParserFormatException(os.str());
	}

	size_t kw_size = sizeof(keywords) / sizeof(keywords[0]);
	size_t i = 0;
	for (; i < kw_size; ++i)
	{
		if (m_it->data == keywords[i].name)
		{
			if (keywords[i].e_block == comp)
			{
				throw ParserFormatException(m_it->data + "' can't be outside a location block");
			}
			if (keywords[i].e_uniqness == uniq)
			{
				std::vector<p_Directive>::const_iterator d_ite = t.directives.end();
				for (std::vector<p_Directive>::const_iterator d_it = t.directives.begin();
					 d_it != d_ite; ++d_it)
				{
					if (d_it->name == m_it->data)
					{
						std::ostringstream os;
						os << "location can't have multiple '" << m_it->data << "'";
						throw ParserFormatException(os.str());
					}
				}
			}
			break;
		}
	}

	direc.name = m_it->data;
	++m_it;

	int nb_val = 1;
	for (; m_it->type == str_type || m_it->type == int_type; ++m_it, ++nb_val)
	{
		if (keywords[i].max_args < nb_val)
		{
			std::ostringstream os;
			os << "'" << direc.name << "' can't have more than " << keywords[i].max_args
			   << " values";
			throw ParserFormatException(os.str());
		}
		direc.values.push_back(m_it->data);
	}
	if (keywords[i].min_args > nb_val)
	{
		std::ostringstream os;
		os << direc.name << "' needs at least " << keywords[i].min_args << " values";
		throw ParserFormatException(os.str());
	}
	expect(';');
	++m_it;
	t.directives.push_back(direc);
	return direc;
}

p_Location Parser::parseLocation(p_ServerConfig &serv)
{
	++m_it;
	if (m_it->type != str_type)
	{
		throw ParserFormatException("expected a directory for the location block");
	}

	p_Location loc;
	loc.path = m_it->data;
	++m_it;
	expect('{');
	++m_it;

	while (m_it != m_ite && m_it->type != char_rbracket)
	{
		if (m_it->type == res_word && m_it->data == "location")
		{
			throw ParserFormatException("location block can't contain another location block");
		}
		parseDirective(loc, inserv);
	}
	expect('}');
	++m_it;
	serv.locations.push_back(loc);
	return loc;
}

p_ServerConfig Parser::parseServerConfig()
{
	++m_it;
	expect('{');
	++m_it;

	p_ServerConfig serv;

	while (m_it != m_ite && m_it->type != char_rbracket)
	{
		if (m_it->type == res_word && m_it->data == "server")
		{
			throw ParserFormatException("server block can't contain another server block");
		}
		if (m_it->type == res_word && m_it->data == "location")
		{
			parseLocation(serv);
		}
		else
		{
			parseDirective(serv, inloc);
		}
	}
	expect('}');
	++m_it;
	m_config.servers.push_back(serv);
	return serv;
}

void Parser::parseConfig()
{
	while (m_it != m_ite)
	{
		if (m_it->type == res_word && m_it->data == "server")
		{
			parseServerConfig();
		}
		else
		{
			throw ParserFormatException(
				"server block should start with 'server' instead of '" + m_it->data + "'"
			);
		}
	}
}

void Parser::parse(p_Config &config)
{
	parseConfig();
	config = m_config;
}

std::ostream &operator<<(std::ostream &os, const p_Config &c)
{
	std::vector<p_ServerConfig>::const_iterator s_ite = c.servers.end();
	for (std::vector<p_ServerConfig>::const_iterator s_it = c.servers.begin(); s_it != s_ite; ++s_it)
	{
		os << "***SERVER***" << std::endl;
		std::vector<p_Location>::const_iterator l_ite = s_it->locations.end();
		for (std::vector<p_Location>::const_iterator l_it = s_it->locations.begin(); l_it != l_ite;
			 ++l_it)
		{
			os << "\tPath: " << l_it->path << std::endl;
			std::vector<p_Directive>::const_iterator d_ite = l_it->directives.end();
			for (std::vector<p_Directive>::const_iterator d_it = l_it->directives.begin();
				 d_it != d_ite; ++d_it)
			{
				os << "\t\tName: " << d_it->name << std::endl;
				os << "\t\tValues: ";
				std::vector<std::string>::const_iterator str_ite = d_it->values.end();
				for (std::vector<std::string>::const_iterator str_it = d_it->values.begin();
					 str_it != str_ite; ++str_it)
				{
					os << *str_it << " ";
				}
				os << std::endl;
			}
		}
		std::vector<p_Directive>::const_iterator d_ite = s_it->directives.end();
		for (std::vector<p_Directive>::const_iterator d_it = s_it->directives.begin();
			 d_it != d_ite; ++d_it)
		{
			os << "\tName: " << d_it->name << std::endl;
			os << "\tValues: ";
			std::vector<std::string>::const_iterator str_ite = d_it->values.end();
			for (std::vector<std::string>::const_iterator str_it = d_it->values.begin();
				 str_it != str_ite; ++str_it)
			{
				os << *str_it << " ";
			}
			os << std::endl;
		}
	}
	return os;
}
