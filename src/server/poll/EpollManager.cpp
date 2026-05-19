#include "EpollManager.hpp"

#include <iostream>
#include <stdexcept>

#ifdef __linux__

#include <unistd.h>

#include <cstring>
#include <iostream>

EpollManager::EpollManager() : m_epoll_fd(-1), m_events_list() {
  std::cout << "Linus OS EpollManager active\n";
  m_epoll_fd = epoll_create(1);
  if (m_epoll_fd == -1) throw std::runtime_error("epoll_create failed");
  std::cout << "epoll fd: " << m_epoll_fd << "\n";
}

EpollManager::EpollManager(const EpollManager& epm) { (void)epm; }

EpollManager& EpollManager::operator=(const EpollManager& epm) {
  (void)epm;
  return *this;
}

EpollManager::~EpollManager() {
  if (m_epoll_fd != -1) close(m_epoll_fd);
  std::cout << "epoll close fd: " << m_epoll_fd << "\n";
}

bool EpollManager::addSocket(const int fd, const int filter, void* udata) {
  (void)filter;
  struct epoll_event ev = {};
  std::memset(&ev, 0, sizeof(ev));

  const int ep_filter = filter == TYPE_READ ? EPOLLIN : EPOLLOUT;
  ev.events = ep_filter;
  ev.data.ptr = udata;

  if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, fd, &ev) == -1) return false;

  std::cout << "epoll ctl add, socket add fd: " << fd << "\n";
  return true;
}

bool EpollManager::removeSocket(const int fd) {
  struct epoll_event ev = {};
  std::memset(&ev, 0, sizeof(ev));

  if (epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, fd, &ev)) return false;

  std::cout << "epoll ctl del, socket removed fd: " << fd << "\n";
  return true;
}

int EpollManager::waitForEvents(const int timeout_ms) {
  std::cout << "waitForEvents timeout_ms: " << timeout_ms << "\n";
  int n_ev = epoll_wait(m_epoll_fd, m_events_list, N_EP_EVENTS_BUF, timeout_ms);
  std::cout << "waitForEvents 2 timeout_ms: " << timeout_ms << "\n";

  return n_ev;
}

void* EpollManager::getUserData(const int idx) {
  return m_events_list[idx].data.ptr;
}

int EpollManager::getEventFd(const int idx) {}

bool EpollManager::isReadEvent(const int idx) {}

#endif