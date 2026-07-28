#include "Server.hpp"

#include <cstddef>
#include <iostream>

#include "config/ServerConfig.hpp"
#include "transport/endpoint/IEndpoint.hpp"
#include "transport/endpoint/build_endpoints.hpp"
#include "utils/Logger.hpp"

namespace webserv {

Server::Server(const std::vector<config::ServerConfig> &configs)
    : m_endpoints(), m_reactor() {

  transport::buildEndpoints(configs, m_endpoints);

  std::size_t opened = 0;

  for (std::size_t i = 0; i < m_endpoints.size(); ++i) {
    try {
      m_endpoints[i].open(m_reactor);
      ++opened;
    } catch (const std::exception &e) {
      LOG("endpoint skipped: " << e.what());
    }
  }

  if (opened == 0)
    throw config::ServerConfig::Exception("no endpoint could be open");

  LOG("listening on " << opened << (opened == 1 ? " endpoint" : " endpoints"));
}

Server::~Server() {}

void Server::run() { m_reactor.run(); }

} // namespace webserv
