#include "server/transport/endpoint/TcpEndpoint.hpp"

#include <stdexcept>
#include <sys/socket.h>

#include "server/fd/Fd.hpp"
#include "server/handler/IConnectionFactory.hpp"
#include "server/handler/TcpListenerHandler.hpp"
#include "server/reactor/EventType.hpp"
#include "server/reactor/Reactor.hpp"
#include "server/transport/socket.hpp"
#include "server/utils/Logger.hpp"
#include "server/utils/utils.hpp"

namespace webserv {
namespace transport {

TcpEndpoint::TcpEndpoint(const std::string &host, const int port,
                         handler::IConnectionFactory *connection_factory)
    : m_host(host), m_port(port), m_family(),
      m_connection_factory(connection_factory) {}

TcpEndpoint::~TcpEndpoint() { delete m_connection_factory; }

const std::string &TcpEndpoint::getHost() const { return m_host; }

int TcpEndpoint::getPort() const { return m_port; }

const std::string &TcpEndpoint::getFamily() const { return m_family; }

std::string TcpEndpoint::formatEndpoint() const {
  return "tcp:" + m_family + "/" + m_host + ":" + ft::intToString(m_port);
}

void TcpEndpoint::open(reactor::Reactor &reactor) {

  fd::Fd listener_fd(
      socket::createSocket(m_host, m_port, SOCK_STREAM, &m_family));

  if (!listener_fd.setNonBlocking())
    throw IEndpoint::Exception("can't set here " + formatEndpoint() +
                               " non-blocking");

  if (listen(listener_fd.get(), TCP_BACKLOG) == -1)
    throw IEndpoint::Exception("listen failed for " + formatEndpoint());

  if (!reactor.addEventHandler(
          new handler::TcpListenerHandler(listener_fd.release(),
                                          *m_connection_factory),
          reactor::EVENT_READ))
    throw IEndpoint::Exception("reactor registration failed for " +
                               formatEndpoint());

  LOG("endpoint open: " << formatEndpoint());
}

} // namespace transport
} // namespace webserv
