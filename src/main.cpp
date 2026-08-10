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
  LOG("signal " << signum << " received");
  g_running = 0;
}

static void initSignals() {
  std::signal(SIGINT, sigHandler);
  std::signal(SIGTERM, sigHandler);
  std::signal(SIGPIPE, SIG_IGN);
}

void fileCheck(char const *argv) {
  std::string const filename = argv;
  if (filename.substr(filename.find_last_of('.') + 1) != "conf")
    throw ConfigException("Configuration file must have a `.conf` extension.");

  std::ifstream const file(argv);
  if (file.fail())
    throw ConfigException("File could not be opened.");
}

int main(int const argc, char **argv) {
  try {
	if (argc > 2)
    	throw ConfigException("Too many arguments passed.");
    initSignals();
	std::string filepath;
	if (argc == 2)
	{
    	filepath = argv[1];
	}
	else
	{
		filepath = "conf/test.conf";
	}
    fileCheck(filepath.c_str());
    Config const conf(filepath.c_str());
    std::vector<ServerConfig> const &configs = conf.getServerConfigs();

    webserv::Server server(configs);
    server.run();
  } catch (std::exception const &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
