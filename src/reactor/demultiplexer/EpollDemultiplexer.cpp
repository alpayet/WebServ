#include "reactor/demultiplexer/EpollDemultiplexer.hpp"

#include "reactor/EventType.hpp"

#ifdef __linux__

#include <unistd.h>

#include <cstring>
#include <stdexcept>

#include "utils/Logger.hpp"

namespace webserv {
namespace reactor {

uint32_t getEpollMask(const int flag) {
  uint32_t mask = 0;
  if (flag & EVENT_READ)
    mask |= EPOLLIN;
  if (flag & EVENT_WRITE)
    mask |= EPOLLOUT;
  return mask;
}

EpollDemultiplexer::EpollDemultiplexer() : m_epoll_fd(-1), m_events() {
  m_epoll_fd = epoll_create(1);
  if (m_epoll_fd == -1)
    throw std::runtime_error("epoll_create() failed");
  LOG("epoll demultiplexer ready, fd: " << m_epoll_fd);
}

EpollDemultiplexer::~EpollDemultiplexer() {
  if (m_epoll_fd != -1)
    close(m_epoll_fd);
}

bool EpollDemultiplexer::add(const int fd, const int flag) {
  struct epoll_event ev;
  std::memset(&ev, 0, sizeof(ev));
  ev.events = getEpollMask(flag);
  ev.data.fd = fd;
  LOG("epoll add fd: " << fd << " flag: " << flag);
  return epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, fd, &ev) != -1;
}

bool EpollDemultiplexer::modify(const int fd, const int flag) {
  struct epoll_event ev;
  std::memset(&ev, 0, sizeof(ev));
  ev.events = getEpollMask(flag);
  ev.data.fd = fd;
  LOG("epoll modify fd: " << fd << " flag: " << flag);
  return epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, fd, &ev) != -1;
}

bool EpollDemultiplexer::remove(const int fd) {
  LOG("epoll remove fd: " << fd);
  return epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, fd, 0) != -1;
}

int EpollDemultiplexer::wait(const int timeout_ms) {
  return epoll_wait(m_epoll_fd, m_events, EPOLL_MAX_EVENTS, timeout_ms);
}

int EpollDemultiplexer::getEventFd(const int index) const {
  return m_events[index].data.fd;
}

bool EpollDemultiplexer::isReadable(const int index) const {
  return (m_events[index].events & EPOLLIN) != 0;
}

bool EpollDemultiplexer::isWritable(const int index) const {
  return (m_events[index].events & EPOLLOUT) != 0;
}

bool EpollDemultiplexer::isError(const int index) const {
  return (m_events[index].events & (EPOLLERR | EPOLLHUP)) != 0;
}

} // namespace reactor
} // namespace webserv

#endif
