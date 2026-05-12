#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <vector>
# include <string>
# include "Config/Semantic.hpp"
# include "Server/Server.hpp"

class Config
{
	public:
		Config(std::string filename);
		std::vector<Server>	getServers() { return m_servers; };
	private:
		std::vector<Server> m_servers;
};

#endif
