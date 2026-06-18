#include "event_handler/TcpListenerFactory.hpp"

#include "event_handler/TcpListenerHandler.hpp"
#include "protocol/IProtocolFactory.hpp"

namespace webserv {
namespace handler {

TcpListenerFactory::TcpListenerFactory(protocol::IProtocolFactory *app_protocol)
    : m_app_protocol(app_protocol) {}

TcpListenerFactory::~TcpListenerFactory() { delete m_app_protocol; }

reactor::IEventHandler *
TcpListenerFactory::instanceEventHandler(const int fd) const {
  return new TcpListenerHandler(fd, *m_app_protocol);
}

} // namespace handler
} // namespace webserv
