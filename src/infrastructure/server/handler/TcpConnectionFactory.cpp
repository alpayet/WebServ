#include "infrastructure/server/handler/TcpConnectionFactory.hpp"

#include "infrastructure/server/application_protocol/IProtocol.hpp"
#include "infrastructure/server/application_protocol/IProtocolFactory.hpp"
#include "infrastructure/server/handler/ConnectionHandler.hpp"
#include "infrastructure/server/transport_protocol/ITransport.hpp"
#include "infrastructure/server/transport_protocol/TcpTransport.hpp"
#include "infrastructure/storage/file_system/fd/Fd.hpp"

namespace webserv {
namespace handler {

TcpConnectionFactory::TcpConnectionFactory(
    appProtocol::IProtocolFactory *app_protocol_factory)
    : m_app_protocol_factory(app_protocol_factory) {}

TcpConnectionFactory::~TcpConnectionFactory() { delete m_app_protocol_factory; }

IEventHandler *TcpConnectionFactory::create(int const client_fd) const {

  fd::Fd tmp_fd(client_fd);

  transport::ITransport *transport =
      new transport::TcpTransport(tmp_fd.release());

  appProtocol::IProtocol *app_protocol;
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
