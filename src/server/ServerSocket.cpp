#include "ServerSocket.hpp"

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

#include "../utils/utils.hpp"
#include "ServerConfig.hpp"

ServerSocket::ServerSocket(const std::string& host, const int port)
    : m_host(host), m_port(port), m_socket_fd(0) {
  init();
}

ServerSocket::~ServerSocket() {}

std::string ServerSocket::getHost() const { return m_host; }

int ServerSocket::getPort() const { return m_port; }

static void bindServerSocket(addrinfo* res) {
  addrinfo* p;
  int yes = 1;

  for (p = res; p != NULL; p = p->ai_next) {
    int sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

    if (sockfd == -1) continue;

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
      std::cerr << "setsockopt(SO_REUSEADDR) failed: " << strerror(errno)
                << std::endl;
      return;
    }

    if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sockfd);
      std::cerr << "bind() failed: " << strerror(errno) << std::endl;
      continue;
    }

    break;
    // multiple sockets for ipv4 ipv6?
  }
  freeaddrinfo(res);

  if (!p) std::cerr << "Server failed to bind" << std::endl;
}

void ServerSocket::init() const {
  addrinfo hints = {}, *res;

  hints.ai_flags = AI_PASSIVE;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  const int status = getaddrinfo(
      getHost().c_str(), ft::intToString(getPort()).c_str(), &hints, &res);
  if (status != 0)
    std::cerr << "Error getaddrinfo: " << gai_strerror(status) << std::endl;
  else
    bindServerSocket(res);
}
