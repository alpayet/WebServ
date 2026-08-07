#ifndef TCPENDPOINT_HPP
#define TCPENDPOINT_HPP

#include <string>

#include "infrastructure/server/transport_protocol/endpoint/IEndpoint.hpp"

namespace webserv {

namespace handler {
class IConnectionFactory;
}

namespace transport {

class TcpEndpoint : public IEndpoint {
public:
  TcpEndpoint(std::string const &host, int port,
              handler::IConnectionFactory *connection_factory);
  ~TcpEndpoint();

  std::string const &getHost() const;
  int getPort() const;
  std::string const &getFamily() const;

  void open(reactor::Reactor &reactor);
  std::string formatEndpoint() const;

private:
  TcpEndpoint(TcpEndpoint const &);
  TcpEndpoint &operator=(TcpEndpoint const &);

  std::string m_host;
  int m_port;
  std::string m_family;
  handler::IConnectionFactory *m_connection_factory;
};

} // namespace transport
} // namespace webserv

#endif
