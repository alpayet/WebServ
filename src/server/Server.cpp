#include "Server.hpp"

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

#include "ServerConfig.hpp"
#include "ServerSocket.hpp"

Server::Server() {}

Server::Server(std::vector<ServerConfig> configs) {
  for (size_t i = 0; i < configs.size(); ++i) {
    int port = configs[i].getPort();
    if (m_sockets.find(port) == m_sockets.end())
      m_sockets[port] = new ServerSocket(configs[i].getHost(), port);
  }
}

Server::Server(const Server& server) { (void)server; }

Server& Server::operator=(const Server& server) {
  (void)server;
  return *this;
}

Server::~Server() {}

void Server::run() {}
