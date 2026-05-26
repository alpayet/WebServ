#ifndef PARSER_HPP
# define PARSER_HPP

# include <vector>
# include <string>
# include <iterator>
# include "Config/Tokenizer.hpp"
# include "Config/Config.hpp"

struct p_Directive
{
	std::string					name;
	std::vector<std::string>	values;
};

struct p_Location
{
	std::string					path;
	std::vector<p_Directive>	directives;
};

struct p_Server
{
	std::vector<p_Directive>	directives;
	std::vector<p_Location>		locations;
};

struct p_Config
{
	std::vector<p_Server> servers;
};
		
class ParserFormatException : public ConfigException
{
	public:
		ParserFormatException(const std::string& msg) throw() : ConfigException("Error\nWrongly formatted file, " + msg) {};
};

class Parser
{
	public:
		Parser(const std::vector<Token>& tokens);
		~Parser() {};

		p_Config	getConfig() const;
		void		parse(p_Config& config);

	private:
		Parser(Parser& other);
		Parser& operator=(Parser& other);

		const std::vector<Token>			m_tokens;
		std::vector<Token>::const_iterator	m_it;
		std::vector<Token>::const_iterator	m_ite;

		p_Config	m_config;
		template<typename T>
		p_Directive	parseDirective(T& t, e_block comp);
		p_Location	parseLocation(p_Server& serv);
		p_Server	parseServer();
		void		parseConfig();
		void	expect(char c);
};

std::ostream& operator<<(std::ostream& os, const p_Config& c);

#endif
