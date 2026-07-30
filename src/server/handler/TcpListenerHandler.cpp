#include "server/handler/TcpListenerHandler.hpp"

#include "server/handler/IConnectionFactory.hpp"
#include "server/reactor/EventType.hpp"
#include "server/reactor/Reactor.hpp"
#include "server/transport/socket.hpp"
#include "server/utils/Logger.hpp"
#include "server/utils/utils.hpp"

namespace webserv {
namespace handler {

TcpListenerHandler::TcpListenerHandler(
    const int listen_fd, const IConnectionFactory &connection_factory)
    : m_listener_fd(listen_fd), m_connection_factory(connection_factory) {}

TcpListenerHandler::~TcpListenerHandler() {}

int TcpListenerHandler::getFd() const { return m_listener_fd.get(); }

void TcpListenerHandler::onWritable(reactor::Reactor &) {}

void TcpListenerHandler::onReadable(reactor::Reactor &reactor) {

  const int client_fd = transport::socket::accept(m_listener_fd.get());

  if (client_fd < 0)
    return;

  fd::Fd tmp_fd(client_fd);

  if (!tmp_fd.setNonBlocking()) {
    DEBUG("can't set fd " << client_fd << " non-blocking so delete it");
    return;
  }

  try {
    IEventHandler *handler = m_connection_factory.create(tmp_fd.release());

    reactor.addEventHandler(handler, reactor::EVENT_READ);
  } catch (const std::exception &e) {
    DEBUG("can't add new client after accept, remove client fd: "
          << client_fd << ": " << e.what());
    return;
  }

  LOG("accepted client fd: " << client_fd);
}

} // namespace handler
} // namespace webserv
