#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <sys/types.h>

#include <cstddef>
#include <string>

namespace webserv {
namespace transport {

class Socket {
public:
  explicit Socket(int fd);
  ~Socket();

  int getFd() const;

  int accept() const;
  ssize_t recv(char *buf, std::size_t len) const;
  ssize_t send(const char *buf, std::size_t len) const;

  static int configure(const std::string &host, int port, int socktype);

private:
  Socket(const Socket &);
  Socket &operator=(const Socket &);

  int m_fd;
};

} // namespace transport
} // namespace webserv

#endif
