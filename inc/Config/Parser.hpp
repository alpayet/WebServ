#ifndef PARSER_HPP
# define PARSER_HPP

# include <vector>
# include "Tokenizer.hpp"
# include <string>
# include <map>
# include <iterator>

// # include "Server.hpp"

struct p_Directive
{
	std::string					name;
	std::vector<std::string>	values;
};

struct p_Location
{
	std::string				path;
	std::vector<p_Directive>	directives;
};

struct p_Server
{
	std::vector<p_Directive>	directives;
	std::vector<p_Location>	locations;
};

struct p_Config
{
	std::vector<p_Server> servers;
};

class Parser
{
	public:
		/** CONSTRUCTORS */
		Parser(const std::vector<Token>& tokens);
		Parser(Parser& other);
		~Parser();

		p_Config	getConfig() const;
		bool	parse(p_Config& config);

	private:
		const std::vector<Token>			m_tokens;
		std::vector<Token>::const_iterator	m_it;
		std::vector<Token>::const_iterator	m_ite;

		Parser	operator=(Parser& other);
		p_Config	m_config;
		bool	parseDirective(p_Server& serv);
		bool	parseDirective(p_Location& location);
		bool	parseLocation(p_Server& serv);
		bool	parseServer();
		bool	parseConfig();
		bool	expect(char c);
};

std::ostream& operator<<(std::ostream& os, const p_Config& c);

#endif
