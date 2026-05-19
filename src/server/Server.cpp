#include "Server.hpp"

#include <unistd.h>

#include <cerrno>
#include <csignal>
#include <cstring>
#include <iostream>

#include "ClientSocket.hpp"
#include "ServerConfig.hpp"
#include "ServerSocket.hpp"

static int g_i = 0;

Server::Server() : m_event_manager(), m_server_sockets(), m_client_sockets() {}

Server::Server(const std::vector<ServerConfig>& configs)
    : m_event_manager(), m_server_sockets(), m_client_sockets() {
  for (std::size_t i = 0; i < configs.size(); ++i) {
    int port = configs[i].getPort();

    if (m_server_sockets.find(port) != m_server_sockets.end()) {
      std::cout << "Port " << port << " already used.\n";
      continue;
    }

    try {
      ServerSocket* socket = new ServerSocket(configs[i].getHost(), port);
      m_server_sockets.insert(std::make_pair(port, socket));
      m_event_manager.addSocket(socket->getFd(), IEventManager::TYPE_READ, 0);
      // gerer erreur
    } catch (const std::exception& e) {
      std::cerr << "Cannot create server socket on port " << port << ": "
                << e.what() << std::endl;
      continue;
    }
  }
}

Server::~Server() {
  std::map<int, ServerSocket*>::iterator it;
  for (it = m_server_sockets.begin(); it != m_server_sockets.end(); ++it) {
    delete it->second;
  }

  std::map<int, ClientSocket*>::iterator it2;
  for (it2 = m_client_sockets.begin(); it2 != m_client_sockets.end(); ++it2) {
    delete it2->second;
  }
}

void Server::handleNewClient(const int fd) {
  if (m_client_sockets.find(fd) != m_client_sockets.end()) {
    std::cout << "Connexion on socket fd: " << fd << " already created.\n";
  }

  try {
    ClientSocket* socket = new ClientSocket(fd);
    m_client_sockets.insert(std::make_pair(fd, socket));
    m_event_manager.addSocket(socket->getFd(), IEventManager::TYPE_READ,
                              socket);
    g_i += 1;
    // gerer erreur
  } catch (const std::exception& e) {
    std::cerr << "Cannot create client socket on port " << fd << ": "
              << e.what() << std::endl;
  }
}

void Server::handleRequest(const ClientSocket* client) {
  std::cout << "Handling request from client fd: " << client->getFd() << "\n";
  sleep(1874919423);
}

void Server::run() {
  std::cout << "Running server ...\n";
  while (running) {
    const int n_events = m_event_manager.waitForEvents(-1);

    std::cout << "n ev : " << n_events << "\n";
    if (n_events == -1) {
      if (errno == EINTR) continue;
      std::cerr << "Error waiting, either kqueue or epoll\n";
      break;
    }

    for (int i = 0; i < n_events; ++i) {
      void* data = m_event_manager.getUserData(i);
      if (!data && g_i < 1)
        handleNewClient(m_event_manager.getEventFd(i));
      else
        handleRequest(static_cast<ClientSocket*>(data));
    }
  }
}
