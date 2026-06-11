#ifndef SERVER_HPP
#define SERVER_HPP

#include <csignal>

class ITransport;
class ITransfer;

extern volatile sig_atomic_t running;

class Server {
 public:
  explicit Server(ITransport* transport, ITransfer* transfer);
  ~Server();

  void run();

 private:
  Server();
  Server(const Server& server);
  Server& operator=(const Server& server);

  ITransport* m_transport;
  ITransfer* m_transfer;

  // To see with Marylene
  // Virtual hosting?
  // Default error pages?
};

#endif  // SERVER_HPP
