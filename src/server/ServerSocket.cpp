#include "ServerSocket.hpp"

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <exception>
#include <iostream>

#include "../utils/utils.hpp"
#include "ServerConfig.hpp"

const std::string ServerSocket::DEFAULT_HOST = "0.0.0.0";

ServerSocket::ServerSocket()
    : m_host(DEFAULT_HOST), m_port(-1), m_socket_fd(-1), m_configs() {}

ServerSocket::ServerSocket(const std::string& host, const int port)
    : m_host(host), m_port(port), m_socket_fd(-1), m_configs() {
  addrinfo hints = {};
  addrinfo* serv_info;

  hints.ai_flags = AI_PASSIVE;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  const int status = getaddrinfo(
      m_host.c_str(), ft::intToString(m_port).c_str(), &hints, &serv_info);

  if (status != 0) throw std::runtime_error(gai_strerror(status));

  bindServerSocket(serv_info);
}

ServerSocket::~ServerSocket() {
  if (m_socket_fd != -1) close(m_socket_fd);
}

std::string ServerSocket::getHost() const { return m_host; }

int ServerSocket::getPort() const { return m_port; }

int ServerSocket::getFd() const { return m_socket_fd; }

void ServerSocket::bindServerSocket(addrinfo* serv_info) {
  addrinfo* p;
  const int yes = 1;

  for (p = serv_info; p != NULL; p = p->ai_next) {
    m_socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (m_socket_fd == -1) continue;

    if (setsockopt(m_socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) ==
        -1) {
      std::cerr << "setsockopt(SO_REUSEADDR) failed: " << strerror(errno)
                << std::endl;
      close(m_socket_fd);
      m_socket_fd = -1;
      continue;
    }

    if (bind(m_socket_fd, p->ai_addr, p->ai_addrlen) == -1) {
      std::cerr << "bind() failed: " << strerror(errno) << std::endl;
      close(m_socket_fd);
      m_socket_fd = -1;
      continue;
    }

    if (listen(m_socket_fd, BACKLOG) == -1) {
      std::cerr << "listen() failed: " << strerror(errno) << std::endl;
      close(m_socket_fd);
      m_socket_fd = -1;
      continue;
    }

    freeaddrinfo(serv_info);
    std::cout << "Server is listening and waiting for connections on port: "
              << m_port << " socket fd: " << getFd() << std::endl;
    return;
  }

  freeaddrinfo(serv_info);
  throw std::runtime_error("ServerSocket: bind/listen failed");
}
