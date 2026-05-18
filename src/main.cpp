#include <csignal>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ostream>
#include <vector>

#include "server/Server.hpp"
#include "server/ServerConfig.hpp"

volatile sig_atomic_t running = 1;

static void sigHandler(int signum) {
  std::cout << "Server received signal " << signum << std::endl;
  (void)signum;
  running = 0;
}

void initSignals() {
  struct sigaction sa_exit = {};
  std::memset(&sa_exit, 0, sizeof(struct sigaction));

  sa_exit.sa_handler = sigHandler;
  sigemptyset(&sa_exit.sa_mask);
  sa_exit.sa_flags = SA_RESTART;

  if (sigaction(SIGINT, &sa_exit, NULL) == -1 ||
      sigaction(SIGTERM, &sa_exit, NULL) == -1) {
    std::cerr << "sigaction failed for SIGINT/SIGTERM" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  struct sigaction sa_ignore = {};
  std::memset(&sa_ignore, 0, sizeof(struct sigaction));

  sa_ignore.sa_handler = SIG_IGN;
  sigemptyset(&sa_ignore.sa_mask);

  if (sigaction(SIGPIPE, &sa_ignore, NULL) == -1) {
    std::cerr << "sigaction failed for SIGPIPE" << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

int main() {
  initSignals();
  std::vector<ServerConfig> configs;

  configs.push_back(ServerConfig("localhost", 3000));
  configs.push_back(ServerConfig("0.0.0.0", 8000));
  configs.push_back(ServerConfig("1", 8080));
  try {
    Server server(configs);

    server.run();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}