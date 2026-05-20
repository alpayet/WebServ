#include "EpollManager.hpp"

#include <iostream>
#include <stdexcept>

#ifdef __linux__

#include <unistd.h>

#include <cstring>
#include <iostream>

#include "../sockets/ClientSocket.hpp"

EpollManager::EpollManager() : m_epoll_fd(-1), m_events_list() {
  std::cout << "Linux OS EpollManager active\n";
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

bool EpollManager::addSocket(const int fd, const int filter) {
  struct epoll_event ev = {};
  std::memset(&ev, 0, sizeof(ev));

  ev.events = filter == TYPE_READ ? EPOLLIN : EPOLLOUT;
  ev.data.fd = fd;

  if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, fd, &ev) == -1) return false;

  std::cout << "epoll ctl add fd: " << ev.data.fd << "\n";
  return true;
}

bool EpollManager::removeSocket(const int fd) {
  struct epoll_event ev = {};
  std::memset(&ev, 0, sizeof(ev));

  if (epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, fd, &ev)) return false;

  std::cout << "epoll ctl del fd: " << fd << "\n";
  return true;
}

int EpollManager::waitForEvents(const int timeout_ms) {
  return epoll_wait(m_epoll_fd, m_events_list, N_EP_EVENTS_BUF, timeout_ms);
}

int EpollManager::getEventFd(const int idx) {
  return m_events_list[idx].data.fd;
}

#endif