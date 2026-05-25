#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <vector>
# include <string>
// # include "Config/Semantic.hpp"
# include "Server/Server.hpp"
# include <exception>

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
		Config(std::string filename); // TODO: use Semantic to init
		std::vector<Server>	getServers() { return m_servers; };
	private:
		std::vector<Server> m_servers;
};

#endif
