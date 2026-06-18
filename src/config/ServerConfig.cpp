#include "config/ServerConfig.hpp"

namespace webserv {
namespace config {

ServerConfig::ConfigException::ConfigException(const std::string& what) throw()
    : std::runtime_error("Config exception: " + what + ".\n") {}

ServerConfig::ServerConfig(const std::string& host, const int port,
                           const TransportProtocol transport,
                           const ApplicativeProtocol app)
    : m_transport(transport),
      m_applicative_protocol(app),
      m_host(host),
      m_port(port),
      m_server_names(),
      m_locations() {}

ServerConfig::~ServerConfig() {}

const std::string& ServerConfig::getHost() const { return m_host; }

int ServerConfig::getPort() const { return m_port; }

ServerConfig::TransportProtocol ServerConfig::getTransport() const {
  return m_transport;
}

ServerConfig::ApplicativeProtocol ServerConfig::getApplicativeProtocol() const {
  return m_applicative_protocol;
}

}
}
