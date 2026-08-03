#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>

#define LOG(s) std::cout << "[webserv] " << s << '\n'

#ifdef WS_DEBUG
#define DEBUG(s) std::cerr << "[debug] " << s << '\n'
#else
#define DEBUG(s) ((void)0)
#endif

class Logger {
public:
  Logger();
  Logger(const std::string &s);
  ~Logger();

private:
  Logger(const Logger &);
  Logger &operator=(const Logger &);
};

#endif
