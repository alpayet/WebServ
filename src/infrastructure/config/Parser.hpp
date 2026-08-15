#ifndef PARSER_HPP
#define PARSER_HPP

#include "infrastructure/config/Config.hpp"
#include "infrastructure/config/Tokenizer.hpp"
#include <iterator>
#include <string>
#include <vector>

namespace webserv {
struct p_Directive
{
	std::string				 name;
	std::vector<std::string> values;
};

struct p_Location
{
	std::string				 path;
	std::vector<p_Directive> directives;
};

struct p_ServerConfig
{
	std::vector<p_Directive> directives;
	std::vector<p_Location>	 locations;
};

struct p_Config
{
	std::vector<p_ServerConfig> servers;
};

class ParserFormatException : public ConfigException
{
  public:
	ParserFormatException(std::string const &msg) throw()
		: ConfigException("Error\nWrongly formatted file, " + msg) {};
};

class Parser
{
  public:
	Parser(std::vector<Token> const &tokens);
	~Parser() {};

	p_Config getConfig() const;
	void	 parse(p_Config &config);

  private:
	Parser(Parser &other);
	Parser &operator=(Parser &other);

	std::vector<Token> const		   m_tokens;
	std::vector<Token>::const_iterator m_it;
	std::vector<Token>::const_iterator m_ite;

	p_Config						  m_config;
	template <typename T> p_Directive parseDirective(T &t, e_block comp);
	p_Location						  parseLocation(p_ServerConfig &serv);
	p_ServerConfig					  parseServerConfig();
	void							  parseConfig();
	void							  expect(char c);
};

std::ostream &operator<<(std::ostream &os, p_Config const &c);
} // namespace webserv

#endif
