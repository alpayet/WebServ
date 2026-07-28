#include "handler/TcpConnectionFactory.hpp"

#include "fd/Fd.hpp"
#include "handler/ConnectionHandler.hpp"
#include "protocol/IProtocol.hpp"
#include "protocol/IProtocolFactory.hpp"
#include "transport/ITransport.hpp"
#include "transport/TcpTransport.hpp"

namespace webserv {
namespace handler {

TcpConnectionFactory::TcpConnectionFactory(
    protocol::IProtocolFactory *app_protocol)
    : m_app_protocol(app_protocol) {}

TcpConnectionFactory::~TcpConnectionFactory() { delete m_app_protocol; }

IEventHandler *TcpConnectionFactory::create(const int client_fd) const {

  fd::Fd tmp_fd(client_fd);

  transport::ITransport *transport =
      new transport::TcpTransport(tmp_fd.release());

  protocol::IProtocol *app_protocol;
  try {
    app_protocol = m_app_protocol->create();
  } catch (...) {
    delete transport;
    throw;
  }

  try {
    return new handler::ConnectionHandler(transport, app_protocol);
  } catch (...) {
    delete app_protocol;
    delete transport;
    throw;
  }
}

} // namespace handler
} // namespace webserv
