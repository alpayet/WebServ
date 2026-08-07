#include "infrastructure/server/transport_protocol/endpoint/TcpEndpoint.hpp"

#include <stdexcept>
#include <sys/socket.h>

#include "infrastructure/server/handler/IConnectionFactory.hpp"
#include "infrastructure/server/handler/TcpListenerHandler.hpp"
#include "infrastructure/server/reactor/EventType.hpp"
#include "infrastructure/server/reactor/Reactor.hpp"
#include "infrastructure/server/transport_protocol/endpoint/EndpointException.hpp"
#include "infrastructure/server/transport_protocol/socket.hpp"
#include "infrastructure/server/utils/Logger.hpp"
#include "infrastructure/server/utils/utils.hpp"
#include "infrastructure/storage/file_system/fd/Fd.hpp"

namespace webserv {
namespace transport {

TcpEndpoint::TcpEndpoint(std::string const &host, int const port,
                         handler::IConnectionFactory *connection_factory)
    : m_host(host), m_port(port), m_family(),
      m_connection_factory(connection_factory) {}

TcpEndpoint::~TcpEndpoint() { delete m_connection_factory; }

std::string const &TcpEndpoint::getHost() const { return m_host; }

int TcpEndpoint::getPort() const { return m_port; }

std::string const &TcpEndpoint::getFamily() const { return m_family; }

std::string TcpEndpoint::formatEndpoint() const {
  return "tcp:" + m_family + "/" + m_host + ":" + ft::intToString(m_port);
}

void TcpEndpoint::open(reactor::Reactor &reactor) {

  fd::Fd listener_fd(
      socket::createSocket(m_host, m_port, SOCK_STREAM, &m_family));

  if (!listener_fd.setNonBlocking())
    throw EndpointException("can't set here " + formatEndpoint() +
                            " non-blocking");

  if (listen(listener_fd.get(), SOMAXCONN) == -1)
    throw EndpointException("listen failed for " + formatEndpoint());

  if (!reactor.addEventHandler(
          new handler::TcpListenerHandler(listener_fd.release(),
                                          *m_connection_factory),
          reactor::EVENT_READ))
    throw EndpointException("reactor registration failed for " +
                            formatEndpoint());

  Logger("listening on: " + formatEndpoint());
}

} // namespace transport
} // namespace webserv
