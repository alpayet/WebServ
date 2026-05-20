#ifndef EPOLLMANAGER_HPP
#define EPOLLMANAGER_HPP

#ifdef __linux__
#include <sys/epoll.h>

#include <vector>

#include "IEventManager.hpp"

#define N_EP_EVENTS_BUF 64

class EpollManager : public IEventManager {
 public:
  EpollManager();
  ~EpollManager();

  bool addSocket(int fd, int filter);
  bool removeSocket(int fd);

  int waitForEvents(int timeout_ms);

  int getEventFd(int index);

 private:
  EpollManager(const EpollManager& epm);
  EpollManager& operator=(const EpollManager& epm);

  struct EpollData {
    int fd;
    void* ptr;
  };

  int m_epoll_fd;
  struct epoll_event m_events_list[N_EP_EVENTS_BUF];
};
#endif

#endif  // EPOLLMANAGER_HPP
