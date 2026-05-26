#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <vector>
# include <string>
# include <exception>
# include "Server/Server.hpp"

class ConfigException : public std::exception
{
	public:
		ConfigException(const std::string& msg) throw() : m_msg(msg) {};
		virtual ~ConfigException() throw() {};
		virtual const char* what() const throw() { return m_msg.c_str(); };
	protected:
		std::string m_msg;
};

class Config
{
	public:
		Config(char* filename); // TODO: use Semantic to init
		const std::vector<Server>&	getServers() const { return m_servers; };
	private:
		std::vector<Server> m_servers;
};

#endif
