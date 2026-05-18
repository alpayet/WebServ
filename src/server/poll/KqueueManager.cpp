#include "KqueueManager.hpp"

#ifdef __APPLE__

#include <unistd.h>

#include <iostream>

KqueueManager::KqueueManager()
    : m_kqueue_fd(-1), m_events_list(), m_nb_events(0) {
  std::cout << "Mac OS KqueueManager active\n";

  m_kqueue_fd = kqueue();

  if (m_kqueue_fd == -1) throw std::runtime_error("kqueue() failed");
}

KqueueManager::KqueueManager(const KqueueManager& kqm)
    : m_kqueue_fd(-1), m_events_list(), m_nb_events(0) {
  (void)kqm;
}

KqueueManager& KqueueManager::operator=(const KqueueManager& kqm) {
  (void)kqm;
  return *this;
}

KqueueManager::~KqueueManager() {
  if (m_kqueue_fd != -1) close(m_kqueue_fd);
}

bool KqueueManager::addSocket(const int fd, const int filter, void* udata) {
  struct kevent sev;
  int k_filter = filter == TYPE_READ ? EVFILT_READ : EVFILT_WRITE;

  EV_SET(&sev, fd, k_filter, EV_ADD | EV_ENABLE, 0, 0, udata);

  if (kevent(m_kqueue_fd, &sev, 1, NULL, 0, NULL) == -1) return false;

  return true;
}

bool KqueueManager::removeSocket(const int fd) {}

int KqueueManager::waitForEvents(const int timeout_ms) {
  timespec timeout = {};

  m_nb_events = kevent(m_kqueue_fd, NULL, 0, m_events_list, N_EVENTS_BUF, NULL);

  // attention ca retourne -1 gerer l'erreur ici?
  return m_nb_events;
}

void* KqueueManager::getUserData(const int idx) {
  return m_events_list[idx].udata;
}

uintptr_t KqueueManager::getEventFd(int idx) {
  return m_events_list[idx].ident;
}

bool KqueueManager::isReadEvent(int idx) {}

#endif