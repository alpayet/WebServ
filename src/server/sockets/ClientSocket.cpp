#include "ClientSocket.hpp"

#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../../utils/server_utils.hpp"
#include "../Server.hpp"

// interdit
#include <arpa/inet.h>

#include <iostream>
#include <stdexcept>

ClientSocket::ClientSocket() : m_socket_fd(-1), m_ip(0), m_buf() {}

ClientSocket::ClientSocket(const int fd) : m_socket_fd(-1), m_ip(0), m_buf() {
  sockaddr_storage sas = {};
  socklen_t addr_size = sizeof(sas);
  char s[INET6_ADDRSTRLEN];

  m_socket_fd = accept(fd, reinterpret_cast<sockaddr*>(&sas), &addr_size);
  if (m_socket_fd == -1) throw std::runtime_error("accept() failed");

  std::cout << "New client socket fd: " << m_socket_fd << "\n";

  fcntl(m_socket_fd, F_SETFL, O_NONBLOCK);

  inet_ntop(sas.ss_family, getInAddr(reinterpret_cast<sockaddr*>(&sas)), s,
            sizeof(s));

  std::cout << "New client connected from: " << s << "\n";
}

ClientSocket::ClientSocket(const ClientSocket& cs)
    : m_socket_fd(-1), m_ip(0), m_buf() {
  (void)cs;
}

ClientSocket& ClientSocket::operator=(const ClientSocket& cs) {
  (void)cs;
  return *this;
}

ClientSocket::~ClientSocket() {
  if (m_socket_fd != -1) close(m_socket_fd);
}

int ClientSocket::getFd() const { return m_socket_fd; }

void ClientSocket::handleEvent(Server* server) { server->handleRequest(this); }