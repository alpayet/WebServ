#ifndef TCPENDPOINT_HPP
#define TCPENDPOINT_HPP

#include <string>

#include "server/transport/endpoint/IEndpoint.hpp"

namespace webserv {

namespace handler {
class IConnectionFactory;
}

namespace transport {

class TcpEndpoint : public IEndpoint {
public:
  TcpEndpoint(const std::string &host, int port,
              handler::IConnectionFactory *connection_factory);
  ~TcpEndpoint();

  const std::string &getHost() const;
  int getPort() const;
  const std::string &getFamily() const;

  void open(reactor::Reactor &reactor);
  std::string formatEndpoint() const;

private:
  TcpEndpoint(const TcpEndpoint &);
  TcpEndpoint &operator=(const TcpEndpoint &);

  std::string m_host;
  int m_port;
  std::string m_family;
  handler::IConnectionFactory *m_connection_factory;
};

} // namespace transport
} // namespace webserv

#endif
