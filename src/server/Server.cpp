#include "Server.hpp"

#include <unistd.h>

#include <cerrno>
#include <csignal>
#include <cstring>
#include <iostream>

#include "ServerConfig.hpp"
#include "sockets/ClientSocket.hpp"
#include "sockets/ISocket.hpp"
#include "sockets/ServerSocket.hpp"

Server::Server() : m_ports_used(), m_event_manager(), m_sockets() {}

Server::Server(const std::vector<ServerConfig>& configs)
    : m_ports_used(), m_event_manager(), m_sockets() {
  m_sockets.resize(1024, NULL);

  for (std::vector<ServerConfig>::const_iterator it_conf = configs.begin();
       it_conf != configs.end(); ++it_conf) {
    const int port = it_conf->getPort();

    if (m_ports_used.find(port) != m_ports_used.end()) {
      std::cout << "Port " << port << " already used.\n";
      continue;
    }

    try {
      ServerSocket* socket = new ServerSocket(it_conf->getHost(), port);

      std::cout << "New server sock, fd: " << socket->getFd() << "\n";
      setSocket(socket->getFd(), socket);
      m_event_manager.addSocket(socket->getFd(), IEventManager::TYPE_READ);
      // gerer erreur
    } catch (const std::exception& e) {
      std::cerr << "Cannot create server socket on port " << port << ": "
                << e.what() << std::endl;
      continue;
    }
  }
}

Server::~Server() {
  std::vector<ISocket*>::iterator it;
  for (it = m_sockets.begin(); it != m_sockets.end(); ++it) {
    delete *it;
  }
  m_sockets.clear();
}

ISocket* Server::getSocket(const int fd) const {
  if (fd < 0 || static_cast<std::size_t>(fd) >= m_sockets.size()) return 0;
  return m_sockets[static_cast<std::size_t>(fd)];
}

void Server::setSocket(const int fd, ISocket* socket) {
  if (fd < 0) return;
  if (static_cast<std::size_t>(fd) >= m_sockets.size()) {
    m_sockets.resize(static_cast<std::size_t>(fd) + 10, 0);
  }
  m_sockets[static_cast<std::size_t>(fd)] = socket;
}

void Server::handleNewClient(const int fd) {
  std::cout << "New client connexion from socket: " << fd << "\n";

  try {
    ClientSocket* socket = new ClientSocket(fd);

    setSocket(socket->getFd(), socket);
    m_event_manager.addSocket(socket->getFd(), IEventManager::TYPE_READ);
    // gerer erreur
  } catch (const std::exception& e) {
    std::cerr << "Cannot create client socket on port " << fd << ": "
              << e.what() << std::endl;
  }
}

void Server::handleRequest(const ClientSocket* client) {
  if (client)
    std::cout << "Handling request from client fd: " << client->getFd() << "\n";
  else
    std::cout << "No client found handle req\n";
  sleep(9999999);
}

void Server::run() {
  std::cout << "Running server ...\n";
  while (running) {
    const int n_events = m_event_manager.waitForEvents(-1);

    if (n_events == -1) {
      if (errno == EINTR) continue;
      std::cerr << "Error waiting, either kqueue or epoll\n";
      break;
    }

    for (int i = 0; i < n_events; ++i) {
      const int fd = m_event_manager.getEventFd(i);
      ISocket* socket = getSocket(fd);

      if (socket) std::cout << "Data received from " << socket->getFd() << "\n";

      if (socket)
        socket->handleEvent(this);
      else
        std::cout << "No socket in run\n";
    }
  }
}
