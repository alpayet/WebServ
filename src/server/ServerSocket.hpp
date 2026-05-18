#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include <netdb.h>

#include <string>
#include <vector>

class ServerConfig;

#define BACKLOG 10

class ServerSocket {
 public:
  explicit ServerSocket(const std::string&, int);
  ~ServerSocket();

  std::string getHost() const;
  int getPort() const;
  int getFd() const;

 private:
  ServerSocket();
  ServerSocket(const ServerSocket&);
  ServerSocket& operator=(const ServerSocket&);

  static const std::string DEFAULT_HOST;

  const std::string m_host;
  const int m_port;
  int m_socket_fd;
  std::vector<ServerConfig> m_configs;

  void init();
  void bindServerSocket(addrinfo*);
};

#endif  // SERVERSOCKET_HPP
