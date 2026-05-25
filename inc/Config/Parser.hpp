#ifndef PARSER_HPP
# define PARSER_HPP

# include <vector>
# include "Tokenizer.hpp"
# include <string>
# include <map>
# include <iterator>
# include <exception>

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

class Parser
{
	public:
		Parser(const std::vector<Token>& tokens);
		~Parser() {};

		p_Config	getConfig() const;
		void		parse(p_Config& config);

		class ParserException : public std::exception
		{
			public:
				ParserException(const std::string& msg) throw() : m_msg(msg) {};
				virtual ~ParserException() throw() {};
				virtual const char* what() const throw() { return m_msg.c_str(); };
			protected:
				std::string m_msg;
		};
		class ParserFormatException : public ParserException
		{
			public:
				ParserFormatException(const std::string& msg) throw() : ParserException("Error\nWrongly formatted file, " + msg) {};
		};

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
