#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include <stdint.h>

class ClientSocket {
 public:
  explicit ClientSocket(int fd);
  ~ClientSocket();

  int getFd() const;
  void setFd(int new_fd);

  static void handleKnownClient(ClientSocket* client);

 private:
  ClientSocket();
  ClientSocket(const ClientSocket& cs);
  ClientSocket& operator=(const ClientSocket& cs);

  int m_socket_fd;
  uint32_t m_ip;
  char* m_buf[4096];
};

#endif  // CLIENTSOCKET_HPP
