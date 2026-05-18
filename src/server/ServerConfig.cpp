#include "ServerConfig.hpp"

const std::string ServerConfig::DEFAULT_HOST = "0.0.0.0";

ServerConfig::ServerConfig()
    : m_host(DEFAULT_HOST), m_port(-1), m_server_names(), m_locations() {}

ServerConfig::ServerConfig(const std::string& h, int p)
    : m_host(h), m_port(p), m_server_names(), m_locations() {}

ServerConfig::~ServerConfig() {}

std::string ServerConfig::getHost() const { return m_host; }

int ServerConfig::getPort() const { return m_port; }