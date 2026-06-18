#include "TcpListenerHandler.hpp"

#include <unistd.h>

#include "ConnectionHandler.hpp"
#include "protocol/IProtocol.hpp"
#include "protocol/IProtocolFactory.hpp"
#include "reactor/EventType.hpp"
#include "reactor/Reactor.hpp"
#include "transport/TcpTransport.hpp"
#include "utils/Logger.hpp"
#include "utils/utils.hpp"

namespace webserv {
namespace handler {

TcpListenerHandler::TcpListenerHandler(
    const int listen_fd, const protocol::IProtocolFactory &app_protocol)
    : m_socket(listen_fd), m_app_protocol(app_protocol) {}

TcpListenerHandler::~TcpListenerHandler() {}

int TcpListenerHandler::getHandlerFd() const { return m_socket.getFd(); }

void TcpListenerHandler::onWritable(reactor::Reactor &) {}

void TcpListenerHandler::onReadable(reactor::Reactor &reactor) {
  const int client_socket_fd = m_socket.accept();
  if (client_socket_fd < 0)
    return;

  if (!ft::setNonBlocking(client_socket_fd)) {
    close(client_socket_fd);
    return;
  }

  protocol::IProtocol *app_protocol = m_app_protocol.create();

  transport::ITransport *transport_protocol;
  try {
    transport_protocol = new transport::TcpTransport(client_socket_fd);
  } catch (const std::exception &e) {
    (void)e;
    delete app_protocol;
    close(client_socket_fd);
    return;
  }

  ConnectionHandler *new_client;
  try {
    new_client = new ConnectionHandler(transport_protocol, app_protocol);
  } catch (const std::exception &e) {
    (void)e;
    delete transport_protocol;
    delete app_protocol;
    return;
  }

  try {
    reactor.registerEventHandler(new_client, reactor::EVENT_READ);
  } catch (const std::exception &e) {
    (void)e;
    delete new_client;
    return;
  }

  LOG("accepted client fd: " << client_socket_fd);
}

} // namespace handler
} // namespace webserv
