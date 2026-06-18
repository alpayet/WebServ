#include "build_endpoints.hpp"

#include <cstddef>
#include <iostream>
#include <stdexcept>

#include "IEndpoint.hpp"
#include "TcpEndpoint.hpp"
#include "config/ServerConfig.hpp"
#include "event_handler/IEventHandlerFactory.hpp"
#include "event_handler/TcpListenerFactory.hpp"
#include "protocol/IProtocolFactory.hpp"
#include "protocol/TestProtocol.hpp"

namespace webserv {
namespace transport {

static protocol::IProtocolFactory *
makeProtocol(const config::ServerConfig &config) {
  switch (config.getApplicativeProtocol()) {
  case config::ServerConfig::APP_HTTP:
    return new protocol::TestProtocolFactory(
        "<h1>Hello Webserv oui oui c'est un grand oui</h1>\n");
  case config::ServerConfig::APP_TEST:
    return new protocol::TestProtocolFactory("OUI app protocol test\n");
  }
  throw std::runtime_error("unknown application protocol");
}

static IEndpoint *makeEndpoint(const config::ServerConfig &config) {
  switch (config.getTransport()) {
  case config::ServerConfig::TRANSPORT_TCP: {
    protocol::IProtocolFactory *app_protocol = makeProtocol(config);

    IEventHandlerFactory *handler_factory;
    try {
      handler_factory = new handler::TcpListenerFactory(app_protocol);
    } catch (const std::exception &e) {
      (void)e;
      delete app_protocol;
      throw;
    }

    try {
      return new TcpEndpoint(config.getHost(), config.getPort(),
                             handler_factory);
    } catch (const std::exception &e) {
      (void)e;
      delete handler_factory;
      throw;
    }
  }
  case config::ServerConfig::TRANSPORT_UDP:
    throw std::runtime_error("UDP transport not implemented");
  }
  throw std::runtime_error("unknown transport protocol");
}

std::vector<IEndpoint *>
buildEndpoints(const std::vector<config::ServerConfig> &configs) {
  std::vector<IEndpoint *> endpoints;
  endpoints.reserve(configs.size());

  try {
    for (std::size_t i = 0; i < configs.size(); ++i)
      endpoints.push_back(makeEndpoint(configs[i]));
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    for (std::size_t i = 0; i < endpoints.size(); ++i)
      delete endpoints[i];
    throw;
  }
  return endpoints;
}

} // namespace transport
} // namespace webserv
