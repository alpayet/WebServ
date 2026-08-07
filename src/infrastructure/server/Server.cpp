#include "infrastructure/server/Server.hpp"

#include <cstddef>
#include <iostream>

#include "infrastructure/config/Config.hpp"
#include "infrastructure/config/ServerConfig.hpp"
#include "infrastructure/server/transport_protocol/endpoint/IEndpoint.hpp"
#include "infrastructure/server/transport_protocol/endpoint/build_endpoints.hpp"
#include "infrastructure/server/utils/Logger.hpp"
#include "utils/utils.hpp"

namespace webserv {

Server::Server(std::vector<ServerConfig> const &configs)
    : m_endpoints(), m_reactor() {

  transport::buildEndpoints(configs, m_endpoints);

  std::size_t opened = 0;

  for (std::size_t i = 0; i < m_endpoints.size(); ++i) {
    try {
      m_endpoints[i].open(m_reactor);
      ++opened;
    } catch (std::exception const &e) {
      LOG("endpoint skipped: " << e.what());
    }
  }

  if (opened == 0)
    throw ConfigException("no endpoint could be open");

  Logger("listening on " + ft::intToString(static_cast<int>(opened)) +
         (opened == 1 ? " endpoint" : " endpoints"));
}

Server::~Server() {}

void Server::run() { m_reactor.run(); }

} // namespace webserv
