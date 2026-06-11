#ifndef TCPTRANSPORT_HPP
#define TCPTRANSPORT_HPP

#define BACKLOG 10

#include <set>
#include <string>

#include "../../poll/OsSelector.hpp"
#include "../ITransport.hpp"
#include "TcpSocket.hpp"

class ServerConfig;
class ClientSocket;

class TcpTransport : public ITransport {
 public:
  explicit TcpTransport(const std::vector<ServerConfig>& config);
  ~TcpTransport();

  void init();

  std::vector<int> getReadableFds();

  std::string processEvent(int fd);
  void sendResponse(int fd, const std::string& data);

  void closeConnection(int fd);

  TcpSocket& getSocket(int fd);
  void setSocket(int fd, int port, TcpSocket::TcpSockType type);

 private:
  TcpTransport();
  TcpTransport(const TcpTransport&);
  TcpTransport& operator=(const TcpTransport&);

  const std::vector<ServerConfig>& m_config;
  std::set<int> m_ports_used;
  EventManager m_event_manager;
  std::vector<TcpSocket> m_sockets;

  int initServerSocket(const std::string& host, int port);
  void handleNewClient(int fd);
  std::string handleClientRequest(int fd);
};

#endif  // TCPTRANSPORT_HPP
