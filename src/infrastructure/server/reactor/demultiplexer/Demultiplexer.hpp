#ifndef DEMULTIPLEXER_HPP
#define DEMULTIPLEXER_HPP

#ifdef __linux__
#include "infrastructure/server/reactor/demultiplexer/EpollDemultiplexer.hpp"
#elif defined(__APPLE__)
#include "infrastructure/server/reactor/demultiplexer/KqueueDemultiplexer.hpp"
#else
#error "Unsupported platform: no epoll or kqueue demultiplexer available"
#endif

namespace webserv {
namespace reactor {

#ifdef __linux__
typedef EpollDemultiplexer Demultiplexer;
#elif defined(__APPLE__)
typedef KqueueDemultiplexer Demultiplexer;
#endif

} // namespace reactor
} // namespace webserv

#endif
