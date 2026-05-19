#ifndef SERVER_HPP
#define SERVER_HPP

#include <csignal>
#include <map>
#include <vector>

#include "poll/OsSelector.hpp"

class ClientSocket;
class ServerConfig;
class ServerSocket;

#define SERVER_PORT "6969"

extern volatile sig_atomic_t running;

class Server {
 public:
  explicit Server(const std::vector<ServerConfig>& config);
  void run();
  ~Server();

 private:
  Server();
  Server(const Server& server);
  Server& operator=(const Server& server);

  void handleNewClient(int fd);
  void handleRequest(const ClientSocket* client);

  EventManager m_event_manager;
  std::map<int, ServerSocket*> m_server_sockets;
  std::map<int, ClientSocket*> m_client_sockets;

  // To see with Marylene
  // Virtual hosting?
  // Default error pages?
};

#endif  // SERVER_HPP
