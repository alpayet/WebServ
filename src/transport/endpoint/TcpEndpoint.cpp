#include "transport/endpoint/TcpEndpoint.hpp"

#include <sys/socket.h>
#include <unistd.h>

#include <stdexcept>

#include "event_handler/IEventHandler.hpp"
#include "event_handler/IEventHandlerFactory.hpp"
#include "reactor/EventType.hpp"
#include "reactor/Reactor.hpp"
#include "transport/Socket.hpp"
#include "utils/Logger.hpp"
#include "utils/utils.hpp"

#define TCP_BACKLOG 128

namespace webserv {
namespace transport {

TcpEndpoint::TcpEndpoint(const std::string &host, const int port,
                         IEventHandlerFactory *handler_factory)
    : m_host(host), m_port(port), m_handler_factory(handler_factory) {}

TcpEndpoint::~TcpEndpoint() { delete m_handler_factory; }

void TcpEndpoint::openEndpoint(reactor::Reactor &reactor) {
  const int tcp_listener_socket_fd =
      Socket::configure(m_host, m_port, SOCK_STREAM);

  if (!ft::setNonBlocking(tcp_listener_socket_fd) ||
      listen(tcp_listener_socket_fd, TCP_BACKLOG) == -1) {
    close(tcp_listener_socket_fd);
    throw std::runtime_error("listen failed for " + m_host + ":" +
                             ft::intToString(m_port));
  }

  reactor::IEventHandler *event_handler;
  try {
    event_handler =
        m_handler_factory->instanceEventHandler(tcp_listener_socket_fd);
  } catch (const std::exception &e) {
    (void)e;
    close(tcp_listener_socket_fd);
    throw;
  }

  try {
    reactor.registerEventHandler(event_handler, reactor::EVENT_READ);
  } catch (const std::exception &e) {
    (void)e;
    delete event_handler;
    throw;
  }

  LOG("TCP endpoint opened, listening on "
      << m_host << ":" << m_port << " fd: " << tcp_listener_socket_fd);
}

} // namespace transport
} // namespace webserv
