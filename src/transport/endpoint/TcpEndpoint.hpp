#ifndef TCPENDPOINT_HPP
#define TCPENDPOINT_HPP

#include <string>

#include "IEndpoint.hpp"

namespace webserv {
namespace transport {

class IEventHandlerFactory;

class TcpEndpoint : public IEndpoint {
public:
  TcpEndpoint(const std::string &host, int port,
              IEventHandlerFactory *handler_factory);
  ~TcpEndpoint();

  void openEndpoint(reactor::Reactor &reactor);

private:
  TcpEndpoint(const TcpEndpoint &);
  TcpEndpoint &operator=(const TcpEndpoint &);

  std::string m_host;
  int m_port;
  IEventHandlerFactory *m_handler_factory;
};

} // namespace transport
} // namespace webserv

#endif
