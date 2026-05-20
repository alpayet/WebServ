#ifndef SERVER_HPP
#define SERVER_HPP

#include <csignal>
#include <set>
#include <vector>

#include "poll/OsSelector.hpp"

class ISocket;
class ClientSocket;
class ServerConfig;
class ServerSocket;

#define SERVER_PORT "6969"
#define N_SOCKETS 1024

extern volatile sig_atomic_t running;

class Server {
 public:
  explicit Server(const std::vector<ServerConfig>& config);
  ~Server();

  ISocket* getSocket(int fd) const;
  void setSocket(int fd, ISocket* socket);

  void run();
  void handleNewClient(int fd);
  void handleRequest(const ClientSocket* client);

 private:
  Server();
  Server(const Server& server);
  Server& operator=(const Server& server);

  std::set<int> m_ports_used;
  EventManager m_event_manager;
  std::vector<ISocket*> m_sockets;

  // To see with Marylene
  // Virtual hosting?
  // Default error pages?
};

#endif  // SERVER_HPP
