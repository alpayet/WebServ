#ifndef EPOLLMANAGER_HPP
#define EPOLLMANAGER_HPP

#ifdef __linux__
#include <sys/epoll.h>

#include <vector>

#include "IEventManager.hpp"

class EpollManager : public IEventManager {
 public:
  EpollManager();
  ~EpollManager();

  bool addSocket(int fd, int filter, void* udata);
  bool removeSocket(int fd);

  int waitForEvents(int timeout_ms);

  void* getUserData(int index);
  uintptr_t getEventFd(int index);
  bool isReadEvent(int index);

 private:
  EpollManager(const EpollManager&);
  EpollManager& operator=(const EpollManager&);

  int m_epoll_fd;
  std::vector<struct epoll_event> m_epevents;
};
#endif

#endif  // EPOLLMANAGER_HPP
