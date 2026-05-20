#ifndef ISOCKET_HPP
#define ISOCKET_HPP

class Server;

class ISocket {
 public:
  virtual ~ISocket() {}

  virtual int getFd() const = 0;
  virtual void handleEvent(Server* server) = 0;
};

#endif  // ISOCKET_HPP
