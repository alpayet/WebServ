#ifndef SERVER_HPP
#define SERVER_HPP

#include <map>
#include <vector>

class ServerConfig;
class ServerSocket;

#define SERVER_PORT "6969"
#define BACKLOG 10

class Server {
 public:
  Server(std::vector<ServerConfig>);
  void run();

 private:
  Server();
  Server(const Server&);
  Server& operator=(const Server&);
  ~Server();

  std::map<int, ServerSocket*> m_sockets;

  // To see with Marylene
  // Virtual hosting?
  // Default error pages?
};

#endif  // SERVER_HPP
