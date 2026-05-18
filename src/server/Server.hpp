#ifndef SERVER_HPP
#define SERVER_HPP

#include <csignal>
#include <map>
#include <vector>

#include "poll/OsSelector.hpp"

class ServerConfig;
class ServerSocket;

#define SERVER_PORT "6969"

extern volatile sig_atomic_t running;

class Server {
 public:
  explicit Server(const std::vector<ServerConfig>&);
  void run();
  ~Server();

 private:
  Server();
  Server(const Server&);
  Server& operator=(const Server&);

  std::map<int, ServerSocket*> m_sockets;
  EventManager m_event_manager;

  // To see with Marylene
  // Virtual hosting?
  // Default error pages?
};

#endif  // SERVER_HPP
