#include "Server.hpp"

#include <cstddef>
#include <iostream>
#include <stdexcept>

#include "config/ServerConfig.hpp"
#include "transport/endpoint/IEndpoint.hpp"

namespace webserv {

Server::Server(const std::vector<transport::IEndpoint *> &endpoints)
    : m_reactor(), m_endpoints(endpoints) {
  std::size_t opened = 0;

  for (std::size_t i = 0; i < m_endpoints.size(); ++i) {
    try {
      m_endpoints[i]->openEndpoint(m_reactor);
      ++opened;
    } catch (const std::exception &e) {
      std::cerr << "server: endpoint skipped: " << e.what() << std::endl;
    }
  }

  if (opened == 0) {
    destroyEndpoints();
    throw config::ServerConfig::ConfigException(
        "no endpoint could be established");
  }
}

Server::~Server() { destroyEndpoints(); }

void Server::destroyEndpoints() {
  for (std::size_t i = 0; i < m_endpoints.size(); ++i)
    delete m_endpoints[i];
  m_endpoints.clear();
}

void Server::run() { m_reactor.run(); }

} // namespace webserv
