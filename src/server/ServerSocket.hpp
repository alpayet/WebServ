#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include <string>
#include <vector>

class ServerConfig;

class ServerSocket {
 public:
  ServerSocket(const std::string&, int);
  ~ServerSocket();

  std::string getHost() const;
  int getPort() const;

 private:
  const std::string m_host;
  const int m_port;
  int m_socket_fd;
  std::vector<ServerConfig> m_configs;

  void init() const;
};

#endif  // SERVERSOCKET_HPP
