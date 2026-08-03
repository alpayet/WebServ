#include "server/transport_protocol/TcpTransport.hpp"

#include "server/transport_protocol/socket.hpp"

#include <vector>

namespace webserv {
namespace transport {

TcpTransport::TcpTransport(const int fd) : m_fd(fd) {}

TcpTransport::~TcpTransport() {}

int TcpTransport::getFd() const { return m_fd.get(); }

ssize_t TcpTransport::read(char *buf, std::size_t len) {
  return socket::recv(m_fd.get(), buf, len);
}

ssize_t TcpTransport::write(const char *buf, std::size_t len) {
  return socket::send(m_fd.get(), buf, len);
}

} // namespace transport
} // namespace webserv
