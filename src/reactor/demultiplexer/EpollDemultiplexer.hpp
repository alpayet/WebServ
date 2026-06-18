#ifndef EPOLLDEMULTIPLEXER_HPP
#define EPOLLDEMULTIPLEXER_HPP

#ifdef __linux__

#include <sys/epoll.h>

#include "reactor/EventType.hpp"
#include "reactor/demultiplexer/IEventDemultiplexer.hpp"

#define EPOLL_MAX_EVENTS 64

namespace webserv {
namespace reactor {

class EpollDemultiplexer : public IEventDemultiplexer {
public:
  EpollDemultiplexer();
  ~EpollDemultiplexer();

  bool add(int fd, int flag);
  bool modify(int fd, int flag);
  bool remove(int fd);

  int wait(int timeout_ms);

  int getEventFd(int index) const;
  bool isReadable(int index) const;
  bool isWritable(int index) const;
  bool isError(int index) const;

private:
  EpollDemultiplexer(const EpollDemultiplexer &);
  EpollDemultiplexer &operator=(const EpollDemultiplexer &);

  int m_epoll_fd;
  struct epoll_event m_events[EPOLL_MAX_EVENTS];
};

} // namespace reactor
} // namespace webserv

#endif

#endif
