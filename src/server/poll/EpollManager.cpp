#include "EpollManager.hpp"

#include <stdexcept>

#ifdef __linux__

#include <unistd.h>

#include <iostream>

EpollManager::EpollManager() : m_epoll_fd(-1), m_epevents() {
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
}

bool EpollManager::removeSocket(const int fd) {}

int EpollManager::waitForEvents(const int timeout_ms) {}

void* EpollManager::getUserData(const int idx) {}

uintptr_t EpollManager::getEventFd(const int idx) {}

bool EpollManager::isReadEvent(const int idx) {}

#endif