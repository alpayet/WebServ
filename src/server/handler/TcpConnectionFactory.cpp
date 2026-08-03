#include "server/handler/TcpConnectionFactory.hpp"

#include "server/applicative_protocol/IProtocol.hpp"
#include "server/applicative_protocol/IProtocolFactory.hpp"
#include "server/fd/Fd.hpp"
#include "server/handler/ConnectionHandler.hpp"
#include "server/transport_protocol/ITransport.hpp"
#include "server/transport_protocol/TcpTransport.hpp"

namespace webserv {
namespace handler {

TcpConnectionFactory::TcpConnectionFactory(
    protocol::IProtocolFactory *app_protocol_factory)
    : m_app_protocol_factory(app_protocol_factory) {}

TcpConnectionFactory::~TcpConnectionFactory() { delete m_app_protocol_factory; }

IEventHandler *TcpConnectionFactory::create(const int client_fd) const {

  fd::Fd tmp_fd(client_fd);

  transport::ITransport *transport =
      new transport::TcpTransport(tmp_fd.release());

  protocol::IProtocol *app_protocol;
  try {
    app_protocol = m_app_protocol_factory->create();
  } catch (...) {
    delete transport;
    throw;
  }

  try {
    return new ConnectionHandler(transport, app_protocol);
  } catch (...) {
    delete app_protocol;
    delete transport;
    throw;
  }
}

} // namespace handler
} // namespace webserv
