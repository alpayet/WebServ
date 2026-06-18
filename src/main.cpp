#include <csignal>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "Server.hpp"
#include "config/ServerConfig.hpp"
#include "transport/endpoint/build_endpoints.hpp"
#include "utils/Logger.hpp"

using namespace webserv;

volatile sig_atomic_t running = 1;

static void sigHandler(const int signum) {
  LOG("Signal " << signum << " received");
  (void)signum;
  running = 0;
}

static void initSignals() {
  std::signal(SIGINT, sigHandler);
  std::signal(SIGTERM, sigHandler);
  std::signal(SIGPIPE, SIG_IGN);
}

int main() {
  initSignals();

  std::vector<config::ServerConfig> configs;

  configs.push_back(config::ServerConfig("localhost", 3000));
  configs.push_back(config::ServerConfig("0.0.0.0", 8000,
                                         config::ServerConfig::TRANSPORT_TCP,
                                         config::ServerConfig::APP_TEST));
  configs.push_back(config::ServerConfig("localhost", 3000));

  try {
    const std::vector<transport::IEndpoint *> endpoints =
        transport::buildEndpoints(configs);

    Server server(endpoints);
    server.run();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
