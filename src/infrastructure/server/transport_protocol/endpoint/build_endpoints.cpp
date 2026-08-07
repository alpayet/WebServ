#include "infrastructure/server/transport_protocol/endpoint/build_endpoints.hpp"

#include <cstddef>

#include "infrastructure/config/Config.hpp"
#include "infrastructure/config/ServerConfig.hpp"
#include "infrastructure/server/application_protocol/IProtocolFactory.hpp"
#include "infrastructure/server/application_protocol/TestProtocol.hpp"
#include "infrastructure/server/application_protocol/http/ProtocolFactory.hpp"
#include "infrastructure/server/handler/IConnectionFactory.hpp"
#include "infrastructure/server/handler/TcpConnectionFactory.hpp"
#include "infrastructure/server/transport_protocol/endpoint/Endpoints.hpp"
#include "infrastructure/server/transport_protocol/endpoint/IEndpoint.hpp"
#include "infrastructure/server/transport_protocol/endpoint/TcpEndpoint.hpp"
#include "infrastructure/server/utils/Logger.hpp"
#include "infrastructure/server/utils/utils.hpp"

namespace webserv {
namespace transport {

// TODO jai renommer les var local protocol par AppProtocol a voir si il faut
// mettre en camelcase les var local

static appProtocol::IProtocolFactory *
buildProtocol(ServerConfig const &config) {
  switch (config.getApplicativeProtocol()) {
  case ServerConfig::APP_TEST:
    return new appProtocol::TestProtocolFactory("test proto blablabla");
  case ServerConfig::APP_HTTP:
    return new http::ProtocolFactory(config);
  default:
    throw ConfigException("no applicative protocol builder for " +
                          config.getHostname() + ":" +
                          ft::intToString(config.getPort()));
  }
}

static IEndpoint *buildTransport(ServerConfig const &config,
                                 appProtocol::IProtocolFactory *appProtocol) {
  switch (config.getTransportProtocol()) {
  case ServerConfig::TRANSPORT_TCP: {
    handler::IConnectionFactory *connection;

    try {
      connection = new handler::TcpConnectionFactory(appProtocol);
    } catch (...) {
      delete appProtocol;
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
    delete appProtocol;
    throw ConfigException("no transport builder for " + config.getHostname() +
                          ":" + ft::intToString(config.getPort()));
  }
}

void buildEndpoints(std::vector<ServerConfig> const &configs,
                    Endpoints &endpoints) {

  for (std::size_t i = 0; i < configs.size(); ++i) {
    ServerConfig const &config = configs[i];

    appProtocol::IProtocolFactory *appProtocol = buildProtocol(config);
    endpoints.add(buildTransport(config, appProtocol));
  }
}

} // namespace transport
} // namespace webserv
