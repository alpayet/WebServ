#include "server/fd/Fd.hpp"

#include <fcntl.h>
#include <unistd.h>

namespace webserv {
namespace fd {

Fd::Fd() : m_fd(-1) {}

Fd::Fd(const int fd) : m_fd(fd) {}

Fd::~Fd() { reset(); }

int Fd::get() const { return m_fd; }

bool Fd::valid() const { return m_fd >= 0; }

int Fd::release() {
  const int fd = m_fd;
  m_fd = -1;
  return fd;
}

void Fd::reset(const int fd) {
  if (m_fd >= 0)
    close(m_fd);
  m_fd = fd;
}

bool Fd::setNonBlocking() const {
  return m_fd >= 0 && fcntl(m_fd, F_SETFL, O_NONBLOCK) != -1;
}

} // namespace fd
} // namespace webserv
