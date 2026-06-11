#include "TcpTransport.hpp"

#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <iostream>

#include "../../../utils/server_utils.hpp"
#include "../../../utils/utils.hpp"
#include "../../ServerConfig.hpp"

// interdit
#include <arpa/inet.h>

TcpTransport::TcpTransport(const std::vector<ServerConfig>& config)
    : m_config(config), m_ports_used(), m_event_manager(), m_sockets() {
  m_sockets.resize(1024, TcpSocket());
}

TcpTransport::~TcpTransport() {
  for (std::size_t i = 3; i < m_sockets.size(); ++i) {
    if (m_sockets[i].type != TcpSocket::SOCK_NONE) close(static_cast<int>(i));
  }
}

TcpSocket& TcpTransport::getSocket(const int fd) {
  if (fd < 0 || static_cast<std::size_t>(fd) >= m_sockets.size()) {
    throw std::out_of_range("Socket descriptor out of range");
  }
  return m_sockets[static_cast<std::size_t>(fd)];
}

void TcpTransport::setSocket(const int fd, const int port,
                             const TcpSocket::TcpSockType type) {
  if (fd >= static_cast<int>(m_sockets.size())) {
    m_sockets.resize(static_cast<std::size_t>(fd) + 10, TcpSocket());
  }
  TcpSocket& socket = getSocket(fd);
  socket.type = type;
  socket.port = port;
}

void TcpTransport::init() {
  for (std::vector<ServerConfig>::const_iterator it_conf = m_config.begin();
       it_conf != m_config.end(); ++it_conf) {
    const std::string& host = it_conf->getHost();
    const int port = it_conf->getPort();

    try {
      const int socket_fd = initServerSocket(host, port);

      setSocket(socket_fd, it_conf->getPort(), TcpSocket::SOCK_SERVER);
      m_event_manager.addSocket(socket_fd, IEventManager::TYPE_READ);
      // gerer erreur
      std::cout << "New server sock init, fd: " << socket_fd << "\n";
    } catch (const std::exception& e) {
      std::cerr << "Cannot create server socket for host: " << host
                << " on port: " << port << " : " << e.what() << std::endl;
    }
  }
}

std::vector<int> TcpTransport::getReadableFds() {
  std::vector<int> fds;

  fds.reserve(m_sockets.size());

  std::cout << "getReadableFds starting" << std::endl;
  const int n_events = m_event_manager.waitForEvents(-1);

  if (n_events == -1 && errno != EINTR)
    throw std::runtime_error("Kqueue/Epoll failed");

  for (int i = 0; i < n_events; ++i)
    fds.push_back(m_event_manager.getEventFd(i));

  return fds;
}

std::string TcpTransport::processEvent(const int fd) {
  if (fd < 0 || static_cast<std::size_t>(fd) >= m_sockets.size())
    throw std::runtime_error("Kqueue/Epoll failed wrong fd in request");

  const TcpSocket& socket = getSocket(fd);

  if (socket.type == TcpSocket::SOCK_SERVER) {
    try {
      handleNewClient(fd);
    } catch (const std::exception& e) {
      std::cerr << "Cannot create client socket on port " << socket.port
                << " : " << e.what() << std::endl;
    }
  } else if (socket.type == TcpSocket::SOCK_CLIENT) {
    return handleClientRequest(fd);
  } else
    throw std::runtime_error("No socket in run\n");
  return "";
}

void TcpTransport::sendResponse(const int fd, const std::string& data) {
  std::cout << "Handling transport response\n";

  if (send(fd, data.c_str(), data.size(), 0) == -1) {
    std::cerr << "send() error on client fd " << fd << std::endl;
  }
}

void TcpTransport::closeConnection(const int fd) {
  if (fd >= 0 && static_cast<std::size_t>(fd) < m_sockets.size()) {
    m_event_manager.removeSocket(fd);
    close(fd);
    TcpSocket& socket = getSocket(fd);
    socket.type = TcpSocket::SOCK_NONE;
    socket.port = -1;
  }
}

int TcpTransport::initServerSocket(const std::string& host, const int port) {
  addrinfo hints = {};
  addrinfo* serv_info;

  hints.ai_flags = AI_PASSIVE;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  const int status = getaddrinfo(host.c_str(), ft::intToString(port).c_str(),
                                 &hints, &serv_info);

  if (status != 0) throw std::runtime_error(gai_strerror(status));

  addrinfo* p;
  int socket_fd = -1;
  const int yes = 1;

  for (p = serv_info; p != NULL; p = p->ai_next) {
    socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (socket_fd == -1) continue;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) ==
        -1) {
      close(socket_fd);
      continue;
    }
    if (bind(socket_fd, p->ai_addr, p->ai_addrlen) == -1) {
      close(socket_fd);
      continue;
    }
    if (listen(socket_fd, BACKLOG) == -1) {
      close(socket_fd);
      continue;
    }
    break;
  }

  freeaddrinfo(serv_info);

  if (!p)
    throw std::runtime_error("All tries to bind host: " + host + " failed");

  std::cout << "Server is listening and waiting for connections on port: "
            << port << " socket fd: " << socket_fd << std::endl;

  return socket_fd;
}

void TcpTransport::handleNewClient(const int fd) {
  std::cout << "handleNewClient from : " << fd << "\n";

  sockaddr_storage sas = {};
  socklen_t addr_size = sizeof(sas);
  char s[INET6_ADDRSTRLEN];

  const int socket_fd =
      accept(fd, reinterpret_cast<sockaddr*>(&sas), &addr_size);

  if (socket_fd == -1) throw std::runtime_error("accept() failed");

  fcntl(socket_fd, F_SETFL, O_NONBLOCK);

  setSocket(socket_fd, getSocket(fd).port, TcpSocket::SOCK_CLIENT);
  m_event_manager.addSocket(socket_fd, IEventManager::TYPE_READ);
  // gerer erreur

  inet_ntop(sas.ss_family, getInAddr(reinterpret_cast<sockaddr*>(&sas)), s,
            sizeof(s));
  std::cout << "New client connected from: " << s
            << "\tsocket fd: " << socket_fd << "\n";
}

std::string TcpTransport::handleClientRequest(const int fd) {
  std::cout << "Handling request from client fd: " << fd << "\n";

  char buffer[4096];
  const ssize_t bytes_read = recv(fd, buffer, sizeof(buffer), 0);

  if (bytes_read == -1) {
    std::cerr << "recv() error on client fd " << fd << std::endl;
  } else if (bytes_read == 0) {
    std::cout << "Client closed connection on fd " << fd << std::endl;
    closeConnection(fd);
  } else
    std::cout << "Read " << bytes_read << " bytes from client.\n";

  return std::string(buffer, static_cast<std::string::size_type>(bytes_read));
}
