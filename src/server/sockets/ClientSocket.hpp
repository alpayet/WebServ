#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include <stdint.h>

#include "ISocket.hpp"

class ClientSocket : public ISocket {
 public:
  explicit ClientSocket(int fd);
  ~ClientSocket();

  virtual int getFd() const;
  virtual void handleEvent(Server* server);

 private:
  ClientSocket();
  ClientSocket(const ClientSocket& cs);
  ClientSocket& operator=(const ClientSocket& cs);

  int m_socket_fd;
  uint32_t m_ip;
  char* m_buf[4096];
};

#endif  // CLIENTSOCKET_HPP
