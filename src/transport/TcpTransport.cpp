#include "transport/TcpTransport.hpp"

namespace webserv {
namespace transport {

TcpTransport::TcpTransport(const int fd) : m_socket(fd) {}

TcpTransport::~TcpTransport() {}

int TcpTransport::getFd() const { return m_socket.getFd(); }

ssize_t TcpTransport::read(char *buf, const std::size_t len) {
  return m_socket.recv(buf, len);
}

ssize_t TcpTransport::write(const char *buf, const std::size_t len) {
  return m_socket.send(buf, len);
}

} // namespace transport
} // namespace webserv
