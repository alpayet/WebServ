#ifndef LOGGER_HPP
#define LOGGER_HPP

#ifdef WS_DEBUG
#include <iostream>
#define LOG(x) std::cerr << "[webserv] " << x << '\n'
#else
#define LOG(x) ((void)0)
#endif

#endif
