#include <csignal>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "infrastructure/config/Config.hpp"
#include "infrastructure/config/ServerConfig.hpp"
#include "infrastructure/server/Server.hpp"
#include "infrastructure/server/utils/Logger.hpp"

sig_atomic_t volatile g_running = 1;

static void sigHandler(int const signum) {
  (void)signum;
  g_running = 0;
}

static void initSignals() {
  std::signal(SIGINT, sigHandler);
  std::signal(SIGTERM, sigHandler);
  std::signal(SIGPIPE, SIG_IGN);
}

void fileCheck(int const argc, char const *argv) {
  if (argc != 2)
    throw ConfigException("No configuration file passed.");

  std::string const filename = argv;
  if (filename.substr(filename.find_last_of('.') + 1) != "conf")
    throw ConfigException("Configuration file must have a `.conf` extension.");

  std::ifstream const file(argv);
  if (file.fail())
    throw ConfigException("File could not be opened.");
}

int main(int const argc, char **argv) {
  try {
    fileCheck(argc, argv[1]);
    initSignals();
    Config const conf(argv[1]);
    std::vector<ServerConfig> const &configs = conf.getServerConfigs();

    webserv::Server server(configs);
    server.run();
  } catch (std::exception const &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
