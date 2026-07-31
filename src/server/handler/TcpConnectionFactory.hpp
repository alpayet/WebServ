#ifndef TCPCONNECTIONFACTORY_HPP
#define TCPCONNECTIONFACTORY_HPP

#include "server/handler/IConnectionFactory.hpp"

namespace webserv {

namespace protocol {
class IProtocolFactory;
}

namespace handler {

class TcpConnectionFactory : public IConnectionFactory {
public:
  explicit TcpConnectionFactory(
      protocol::IProtocolFactory *app_protocol_factory);
  ~TcpConnectionFactory();

  IEventHandler *create(int client_fd) const;

private:
  TcpConnectionFactory(const TcpConnectionFactory &);
  TcpConnectionFactory &operator=(const TcpConnectionFactory &);

  protocol::IProtocolFactory *m_app_protocol_factory;
};

} // namespace handler
} // namespace webserv

#endif
