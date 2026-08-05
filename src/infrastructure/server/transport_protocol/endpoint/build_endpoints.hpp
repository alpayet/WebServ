#ifndef BUILD_ENDPOINTS_HPP
#define BUILD_ENDPOINTS_HPP

#include <vector>

class ServerConfig;

namespace webserv {
namespace transport {

class Endpoints;

void buildEndpoints(const std::vector<ServerConfig> &configs,
                    Endpoints &endpoints);

} // namespace transport
} // namespace webserv

#endif
