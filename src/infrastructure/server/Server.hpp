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
		explicit Server(const std::vector<ServerConfig>& configs);
		~Server();

		void run();

	private:
		Server(const Server&);
		Server& operator=(const Server&);

		transport::Endpoints m_endpoints;
		reactor::Reactor m_reactor;
	};

} // namespace webserv

#endif
