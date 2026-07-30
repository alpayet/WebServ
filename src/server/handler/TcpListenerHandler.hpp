#ifndef TCPLISTENERHANDLER_HPP
#define TCPLISTENERHANDLER_HPP

#include "server/fd/Fd.hpp"
#include "server/handler/IEventHandler.hpp"

namespace webserv {

namespace reactor {
class Reactor;
}

namespace handler {

class IConnectionFactory;

class TcpListenerHandler : public IEventHandler {
public:
  TcpListenerHandler(int listen_fd,
                     const IConnectionFactory &connection_factory);
  ~TcpListenerHandler();

  int getFd() const;
  void onReadable(reactor::Reactor &reactor);
  void onWritable(reactor::Reactor &reactor);

private:
  TcpListenerHandler(const TcpListenerHandler &);
  TcpListenerHandler &operator=(const TcpListenerHandler &);

  fd::Fd m_listener_fd;
  const IConnectionFactory &m_connection_factory;
};

} // namespace handler
} // namespace webserv

#endif
