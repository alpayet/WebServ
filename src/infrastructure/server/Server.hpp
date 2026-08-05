#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>

#include "infrastructure/server/reactor/Reactor.hpp"
#include "infrastructure/server/transport_protocol/endpoint/Endpoints.hpp"

class ServerConfig;

namespace webserv {

class Server
{
  public:
	explicit Server(std::vector<ServerConfig> const &configs);
	~Server();

	void run();

  private:
	Server(Server const &);
	Server &operator=(Server const &);

	transport::Endpoints m_endpoints;
	reactor::Reactor	 m_reactor;
};

} // namespace webserv

#endif
