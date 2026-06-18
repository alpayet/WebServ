#include "transport/Socket.hpp"

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <stdexcept>

#include "utils/utils.hpp"

namespace webserv {
namespace transport {

Socket::Socket(const int fd) : m_fd(fd) {}

Socket::~Socket() {
  if (m_fd >= 0)
    close(m_fd);
}

int Socket::getFd() const { return m_fd; }

int Socket::accept() const { return ::accept(m_fd, 0, 0); }

ssize_t Socket::recv(char *buf, const std::size_t len) const {
  return ::recv(m_fd, buf, len, 0);
}

ssize_t Socket::send(const char *buf, const std::size_t len) const {
  return ::send(m_fd, buf, len, 0);
}

int Socket::configure(const std::string &host, const int port,
                      const int socktype) {

  addrinfo hints = {};
  std::memset(&hints, 0, sizeof(hints));
  hints.ai_flags = AI_PASSIVE;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = socktype;

  addrinfo *info = 0;
  const int status =
      getaddrinfo(host.c_str(), ft::intToString(port).c_str(), &hints, &info);
  if (status != 0)
    throw std::runtime_error(gai_strerror(status));

  const addrinfo *p = 0;
  int socket_fd = -1;
  const int yes = 1;

  for (p = info; p != 0; p = p->ai_next) {
    socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (socket_fd == -1)
      continue;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) ==
            -1 ||
        bind(socket_fd, p->ai_addr, p->ai_addrlen) == -1) {
      close(socket_fd);
      socket_fd = -1;
      continue;
    }
    break;
  }
  freeaddrinfo(info);

  if (p == 0)
    throw std::runtime_error("bind failed for " + host + ":" +
                             ft::intToString(port));
  return socket_fd;
}

} // namespace transport
} // namespace webserv
