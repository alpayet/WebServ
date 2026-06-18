#ifndef TCPLISTENERFACTORY_HPP
#define TCPLISTENERFACTORY_HPP

#include "IEventHandlerFactory.hpp"

namespace webserv {

namespace protocol {
class IProtocolFactory;
}

namespace handler {

class TcpListenerFactory : public transport::IEventHandlerFactory {
public:
  explicit TcpListenerFactory(protocol::IProtocolFactory *app_protocol);
  ~TcpListenerFactory();

  reactor::IEventHandler *instanceEventHandler(int fd) const;

private:
  TcpListenerFactory(const TcpListenerFactory &);
  TcpListenerFactory &operator=(const TcpListenerFactory &);

  protocol::IProtocolFactory *m_app_protocol;
};

} // namespace handler
} // namespace webserv

#endif
