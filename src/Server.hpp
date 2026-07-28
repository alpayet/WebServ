#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>

#include "reactor/Reactor.hpp"
#include "transport/endpoint/Endpoints.hpp"

namespace webserv {

namespace config {
class ServerConfig;
}

class Server {
public:
  explicit Server(const std::vector<config::ServerConfig> &configs);
  ~Server();

  void run();

private:
  Server(const Server &);
  Server &operator=(const Server &);

  transport::Endpoints m_endpoints;
  reactor::Reactor m_reactor;
};

} // namespace webserv

#endif
