#include "ServerConfig.hpp"

ServerConfig::ServerConfig() {}

ServerConfig::~ServerConfig() {}

std::string ServerConfig::getHost() const { return m_host; }

int ServerConfig::getPort() const { return m_port; }
