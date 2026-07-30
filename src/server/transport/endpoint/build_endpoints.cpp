#include "server/transport/endpoint/build_endpoints.hpp"

#include <cstddef>

#include "infrastructure/config/Config.hpp"
#include "infrastructure/config/ServerConfig.hpp"
#include "server/handler/IConnectionFactory.hpp"
#include "server/handler/TcpConnectionFactory.hpp"
#include "server/protocol/HttpProtocolFactory.hpp"
#include "server/protocol/IProtocolFactory.hpp"
#include "server/protocol/TestProtocol.hpp"
#include "server/transport/endpoint/Endpoints.hpp"
#include "server/transport/endpoint/IEndpoint.hpp"
#include "server/transport/endpoint/TcpEndpoint.hpp"
#include "server/utils/Logger.hpp"
#include "server/utils/utils.hpp"

namespace webserv {
namespace transport {

static protocol::IProtocolFactory *buildProtocol(const ServerConfig &config) {
  switch (config.getApplicativeProtocol()) {
  case ServerConfig::APP_TEST:
    return new protocol::TestProtocolFactory("test proto blablabla");
  case ServerConfig::APP_HTTP:
    return new protocol::HttpProtocolFactory(config);
  default:
    throw ConfigException("no applicative protocol builder for " +
                          config.getHostname() + ":" +
                          ft::intToString(config.getPort()));
  }
}

static IEndpoint *buildTransport(const ServerConfig &config,
                                 protocol::IProtocolFactory *protocol) {
  switch (config.getTransportProtocol()) {
  case ServerConfig::TRANSPORT_TCP: {
    handler::IConnectionFactory *connection;

    try {
      connection = new handler::TcpConnectionFactory(protocol);
    } catch (...) {
      delete protocol;
      throw;
    }

    try {
      return new TcpEndpoint(config.getHostname(), config.getPort(),
                             connection);
    } catch (...) {
      delete connection;
      throw;
    }
  }
  default:
    delete protocol;
    throw ConfigException("no transport builder for " + config.getHostname() +
                          ":" + ft::intToString(config.getPort()));
  }
}

void buildEndpoints(const std::vector<ServerConfig> &configs,
                    Endpoints &endpoints) {

  for (std::size_t i = 0; i < configs.size(); ++i) {
    const ServerConfig &config = configs[i];

    protocol::IProtocolFactory *protocol = buildProtocol(config);
    endpoints.add(buildTransport(config, protocol));
  }
}

} // namespace transport
} // namespace webserv
