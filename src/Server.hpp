#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>

#include "reactor/Reactor.hpp"

namespace webserv {

namespace transport {
class IEndpoint;
}

class Server {
public:
  explicit Server(const std::vector<transport::IEndpoint *> &endpoints);
  ~Server();

  void run();

private:
  Server(const Server &);
  Server &operator=(const Server &);

  void destroyEndpoints();

  reactor::Reactor m_reactor;
  std::vector<transport::IEndpoint *> m_endpoints;
};

} // namespace webserv

#endif
