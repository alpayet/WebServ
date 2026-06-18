#ifndef TCPLISTENERHANDLER_HPP
#define TCPLISTENERHANDLER_HPP

#include "IEventHandler.hpp"
#include "transport/Socket.hpp"

namespace webserv {

namespace reactor {
class Reactor;
}
namespace protocol {
class IProtocolFactory;
}

namespace handler {

class TcpListenerHandler : public reactor::IEventHandler {
public:
  TcpListenerHandler(int listen_fd,
                     const protocol::IProtocolFactory &app_protocol);
  ~TcpListenerHandler();

  int getHandlerFd() const;
  void onReadable(reactor::Reactor &reactor);
  void onWritable(reactor::Reactor &reactor);

private:
  TcpListenerHandler(const TcpListenerHandler &);
  TcpListenerHandler &operator=(const TcpListenerHandler &);

  transport::Socket m_socket;
  const protocol::IProtocolFactory &m_app_protocol;
};

} // namespace handler
} // namespace webserv

#endif
