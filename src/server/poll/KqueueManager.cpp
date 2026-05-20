#include "KqueueManager.hpp"

#ifdef __APPLE__

#include <unistd.h>

#include <iostream>

KqueueManager::KqueueManager() : m_kqueue_fd(-1), m_events_list() {
  std::cout << "Mac OS KqueueManager active\n";

  m_kqueue_fd = kqueue();

  if (m_kqueue_fd == -1) throw std::runtime_error("kqueue() failed");
}

KqueueManager::KqueueManager(const KqueueManager& kqm)
    : m_kqueue_fd(-1), m_events_list() {
  (void)kqm;
}

KqueueManager& KqueueManager::operator=(const KqueueManager& kqm) {
  (void)kqm;
  return *this;
}

KqueueManager::~KqueueManager() {
  if (m_kqueue_fd != -1) close(m_kqueue_fd);
}

bool KqueueManager::addSocket(const int fd, const int filter) {
  struct kevent ev;
  const int kq_filter = filter == TYPE_READ ? EVFILT_READ : EVFILT_WRITE;

  EV_SET(&ev, fd, kq_filter, EV_ADD | EV_ENABLE, 0, 0, 0);

  if (kevent(m_kqueue_fd, &ev, 1, NULL, 0, 0) == -1) return false;

  std::cout << "kqueue socket add fd: " << fd << "\n";

  return true;
}

bool KqueueManager::removeSocket(const int fd) {
  struct kevent ev;

  EV_SET(&ev, fd, 0, EV_DELETE, 0, 0, 0);

  if (kevent(m_kqueue_fd, &ev, 1, NULL, 0, 0) == -1) return false;

  std::cout << "kqueue socket remove fd: " << fd << "\n";

  return true;
}

int KqueueManager::waitForEvents(const int timeout_ms) {
  timespec timeout = {};
  (void)timeout_ms;

  // attention ca retourne -1
  return kevent(m_kqueue_fd, NULL, 0, m_events_list, N_KQ_EVENTS_BUF, 0);
}

int KqueueManager::getEventFd(const int index) {
  return static_cast<int>(m_events_list[index].ident);
}

#endif