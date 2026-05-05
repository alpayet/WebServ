#ifndef PARSER_HPP
# define PARSER_HPP

# include <vector>
# include "Tokenizer.hpp"
# include <string>
# include <map>
# include <iterator>

# include "Server.hpp"

// struct Directive
// {
// 	std::string					name;
// 	std::vector<std::string>	values;
// };

// struct Location
// {
// 	std::string				path;
// 	std::vector<Directive>	directives;
// };

// struct Server
// {
// 	std::vector<Directive>	directives;
// 	std::vector<Location>	locations;
// };

struct Config
{
	std::vector<Server> servers;
};

class Parser
{
	public:
		/** CONSTRUCTORS */
		Parser(const std::vector<Token>& tokens);
		Parser(Parser& other);
		~Parser();

		Config	getConfig() const;
		bool	parse(Config& config);

	private:
		const std::vector<Token>			m_tokens;
		std::vector<Token>::const_iterator	m_it;
		std::vector<Token>::const_iterator	m_ite;

		Parser	operator=(Parser& other);
		Config	m_config;
		bool	parseDirective(Server& serv);
		bool	parseDirective(Location& location);
		bool	parseLocation(Server& serv);
		bool	parseServer();
		bool	parseConfig();
		bool	expect(char c);
};

std::ostream& operator<<(std::ostream& os, const Config& c);

#endif
