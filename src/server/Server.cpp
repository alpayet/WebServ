#include "Server.hpp"

#include <csignal>
#include <cstring>
#include <iostream>

#include "ClientSocket.hpp"
#include "ServerConfig.hpp"
#include "ServerSocket.hpp"

Server::Server() : m_sockets(), m_event_manager() {}

Server::Server(const std::vector<ServerConfig>& configs)
    : m_sockets(), m_event_manager() {
  for (std::size_t i = 0; i < configs.size(); ++i) {
    int port = configs[i].getPort();

    if (m_sockets.find(port) != m_sockets.end()) {
      std::cout << "Port " << port << " already used.\n";
      continue;
    }

    try {
      ServerSocket* socket = new ServerSocket(configs[i].getHost(), port);
      m_sockets.insert(std::make_pair(port, socket));
      m_event_manager.addSocket(socket->getFd(), IEventManager::TYPE_READ,
                                NULL);

    } catch (const std::exception& e) {
      std::cerr << "Cannot create server socket on port " << port << ": "
                << e.what() << std::endl;
      continue;
    }
  }
}

Server::~Server() {
  std::map<int, ServerSocket*>::iterator it;
  for (it = m_sockets.begin(); it != m_sockets.end(); ++it) {
    delete it->second;
  }
}

void Server::run() {
  while (running) {
    const int n_events = m_event_manager.waitForEvents(-1);

    for (int i = 0; i < n_events; ++i) {
      void* data = m_event_manager.getUserData(i);
      int fd = m_event_manager.getEventFd(i);
      std::cout << "event fd loop: " << fd << std::endl;
      if (!data)
        ClientSocket::handleNewClient(fd);
      else
        ClientSocket::handleKnownClient(static_cast<ClientSocket*>(data));
    }
  }
}
