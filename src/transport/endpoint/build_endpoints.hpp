#ifndef BUILD_ENDPOINTS_HPP
#define BUILD_ENDPOINTS_HPP

#include <vector>

namespace webserv {

namespace config {
class ServerConfig;
}

namespace transport {

class Endpoints;

void buildEndpoints(const std::vector<config::ServerConfig> &configs,
                    Endpoints &endpoints);

} // namespace transport
} // namespace webserv

#endif
