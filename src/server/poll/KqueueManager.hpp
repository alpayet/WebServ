#ifndef KQUEUEMANAGER_HPP
#define KQUEUEMANAGER_HPP

#ifdef __APPLE__
#include <sys/event.h>

#include <vector>

#include "IEventManager.hpp"

#define N_KQ_EVENTS_BUF 64

struct kevent;

class KqueueManager : public IEventManager {
 public:
  KqueueManager();
  ~KqueueManager();

  bool addSocket(int fd, int filter);
  bool removeSocket(int fd);

  int waitForEvents(int timeout_ms);

  int getEventFd(int index);

 private:
  KqueueManager(const KqueueManager& kqm);
  KqueueManager& operator=(const KqueueManager& kqm);

  int m_kqueue_fd;
  struct kevent m_events_list[N_KQ_EVENTS_BUF];
};

#endif

#endif  // KQUEUEMANAGER_HPP
