#ifndef BUILD_LISTENER_HPP
#define BUILD_LISTENER_HPP

#include <vector>

namespace webserv {

namespace config {
class ServerConfig;
}

namespace transport {

class IEndpoint;

std::vector<IEndpoint *>
buildEndpoints(const std::vector<config::ServerConfig> &configs);

} // namespace transport
} // namespace webserv

#endif
