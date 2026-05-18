#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include <stdint.h>

class ClientSocket {
 public:
  ~ClientSocket();

  static void handleNewClient(int fd);
  static void handleKnownClient(ClientSocket* client);

 private:
  ClientSocket();
  ClientSocket(const ClientSocket&);
  ClientSocket& operator=(const ClientSocket&);

  int m_socket_fd;
  uint32_t m_ip;
  char* buf[4096];
};

#endif  // CLIENTSOCKET_HPP
