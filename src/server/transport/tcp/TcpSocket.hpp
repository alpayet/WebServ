#ifndef TCPSOCKET_HPP
#define TCPSOCKET_HPP

struct TcpSocket {
  TcpSocket();

  enum TcpSockType {
    SOCK_NONE,
    SOCK_SERVER,
    SOCK_CLIENT,
  };

  TcpSockType type;
  int port;
};

#endif  // TCPSOCKET_HPP
