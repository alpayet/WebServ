#ifndef SERVERCONFIG_HPP
#define SERVERCONFIG_HPP

#include <stdexcept>
#include <string>
#include <vector>

namespace webserv {
namespace config {

struct Location {
  std::string path;
  std::string root;
  std::string index;
  std::string cgi;
  std::string methods;
  std::string autoindex;
  int ret;
};

class ServerConfig {
public:
  enum TransportProtocol { TRANSPORT_TCP, TRANSPORT_UDP };

  enum ApplicativeProtocol { APP_HTTP, APP_TEST };

  class ConfigException : public std::runtime_error {
  public:
    explicit ConfigException(const std::string &what) throw();
  };

  ServerConfig(const std::string &host, int port);
  ServerConfig(const std::string &host, int port, TransportProtocol transport,
               ApplicativeProtocol app);
  ~ServerConfig();

  const std::string &getHost() const;
  int getPort() const;
  TransportProtocol getTransport() const;
  ApplicativeProtocol getApplicativeProtocol() const;

  class Exception : public std::runtime_error {
  public:
    explicit Exception(const std::string &what)
        : std::runtime_error("Config error: " + what) {}
  };

private:
  TransportProtocol m_transport;
  ApplicativeProtocol m_applicative_protocol;
  std::string m_host;
  int m_port;
  std::vector<std::string> m_server_names;
  std::vector<Location> m_locations;
};

} // namespace config
} // namespace webserv

#endif
