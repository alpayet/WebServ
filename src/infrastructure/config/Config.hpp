#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "infrastructure/config/ServerConfig.hpp"
#include <stdexcept>
#include <string>
#include <vector>

// TODO: to see
namespace webserv {
class ConfigException : public std::runtime_error
{
  public:
	explicit ConfigException(std::string const &what) : std::runtime_error("Config error: " + what)
	{}
};

class Config
{
  public:
	Config(char const *filename);
	std::vector<ServerConfig> const &getServerConfigs() const { return m_servers; };

  private:
	std::vector<ServerConfig> m_servers;
};
} // namespace webserv

#endif
