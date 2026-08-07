#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <vector>
# include <string>
# include <stdexcept>
# include "infrastructure/config/ServerConfig.hpp"

//TODO: to see
class ConfigException : public std::runtime_error {
public:
	explicit ConfigException(const std::string &what)
		: std::runtime_error("Config error: " + what) {}
};

class Config
{
	public:
		Config(char* filename);
		const std::vector<ServerConfig>&	getServerConfigs() const { return m_servers; };
	private:
		std::vector<ServerConfig> m_servers;
};

#endif
