#include <csignal>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "infrastructure/config/Config.hpp"
#include "infrastructure/config/ServerConfig.hpp"
#include "server/Server.hpp"
#include "server/utils/Logger.hpp"

volatile sig_atomic_t g_running = 1;

static void sigHandler(const int signum) {
  LOG("signal " << signum << " received");
  g_running = 0;
}

static void initSignals() {
  std::signal(SIGINT, sigHandler);
  std::signal(SIGTERM, sigHandler);
  std::signal(SIGPIPE, SIG_IGN);
}

void fileCheck(const int argc, const char *argv) {
  if (argc != 2)
    throw ConfigException("No configuration file passed.");

  const std::string filename = argv;
  if (filename.substr(filename.find_last_of('.') + 1) != "conf")
    throw ConfigException("Configuration file must have a `.conf` extension.");

  const std::ifstream file(argv);
  if (file.fail())
    throw ConfigException("File could not be opened.");
}

int main(const int argc, char **argv) {
  try {
    fileCheck(argc, argv[1]);
    initSignals();
    const Config conf(argv[1]);
    const std::vector<ServerConfig> &configs = conf.getServerConfigs();

    webserv::Server server(configs);
    server.run();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
