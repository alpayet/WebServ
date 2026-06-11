#include <csignal>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

#include "server/Server.hpp"
#include "server/ServerConfig.hpp"
#include "server/transfer/FakeTransfer.hpp"
#include "server/transport/tcp/TcpTransport.hpp"

volatile sig_atomic_t running = 1;

static void sigHandler(int signum) {
  std::cout << "Server received signal : " << signum << std::endl;
  (void)signum;
  running = 0;
}

void initSignals() {
  if (std::signal(SIGINT, sigHandler) == SIG_ERR) {
    std::cerr << "sigaction failed for SIGINT" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  if (std::signal(SIGTERM, sigHandler) == SIG_ERR) {
    std::cerr << "sigaction failed for SIGINT/SIGTERM" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  if (std::signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
    std::cerr << "sigaction failed for SIGPIPE" << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

int main() {
  initSignals();
  std::vector<ServerConfig> configs;

  configs.push_back(ServerConfig("localhost", 3000));
  configs.push_back(ServerConfig("0.0.0.0", 8000));
  configs.push_back(ServerConfig("localhost", 3000));
  try {
    Server server(new TcpTransport(configs),
                  new FakeTransfer("Hello worldito\n"));

    server.run();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}