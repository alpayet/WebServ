#include "transport/endpoint/build_endpoints.hpp"

#include <cstddef>

#include "config/ServerConfig.hpp"
#include "handler/IConnectionFactory.hpp"
#include "handler/TcpConnectionFactory.hpp"
#include "protocol/IProtocolFactory.hpp"
#include "protocol/TestProtocol.hpp"
#include "transport/endpoint/Endpoints.hpp"
#include "transport/endpoint/IEndpoint.hpp"
#include "transport/endpoint/TcpEndpoint.hpp"
#include "utils/utils.hpp"

namespace webserv {
namespace transport {

static protocol::IProtocolFactory *
buildProtocol(const config::ServerConfig &config) {
  switch (config.getApplicativeProtocol()) {
  case config::ServerConfig::APP_TEST:
    return new protocol::TestProtocolFactory("test proto blablabla");
  default:
    throw config::ServerConfig::Exception(
        "no applicative protocol builder for " + config.getHost() + ":" +
        ft::intToString(config.getPort()));
  }
}

static IEndpoint *buildTransport(const config::ServerConfig &config,
                                 protocol::IProtocolFactory *protocol) {
  switch (config.getTransport()) {
  case config::ServerConfig::TRANSPORT_TCP: {
    handler::IConnectionFactory *connection;

    try {
      connection = new handler::TcpConnectionFactory(protocol);
    } catch (...) {
      delete protocol;
      throw;
    }

    try {
      return new TcpEndpoint(config.getHost(), config.getPort(), connection);
    } catch (...) {
      delete connection;
      throw;
    }
  }
  default:
    delete protocol;
    throw config::ServerConfig::Exception("no transport builder for " +
                                          config.getHost() + ":" +
                                          ft::intToString(config.getPort()));
  }
}

void buildEndpoints(const std::vector<config::ServerConfig> &configs,
                    Endpoints &endpoints) {

  for (std::size_t i = 0; i < configs.size(); ++i) {
    const config::ServerConfig &config = configs[i];

    protocol::IProtocolFactory *protocol = buildProtocol(config);
    endpoints.add(buildTransport(config, protocol));
  }
}

} // namespace transport
} // namespace webserv
