#include "server/utils/Logger.hpp"

#include "server/utils/utils.hpp"

Logger::Logger() {
  std::cout << "[webserv | " << ft::nowFormat() << "] " << "Logger::Logger()"
            << std::endl;
}

Logger::Logger(const std::string &s) {

  std::cout << "[" << ft::nowFormat() << "] " << s << std::endl;
}

Logger::~Logger() {}
