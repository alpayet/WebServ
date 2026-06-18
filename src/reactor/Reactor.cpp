#include "reactor/Reactor.hpp"

#include <csignal>
#include <cstddef>
#include <stdexcept>

#include "event_handler/IEventHandler.hpp"
#include "reactor/EventType.hpp"
#include "utils/Logger.hpp"

extern volatile sig_atomic_t running;

namespace webserv {
namespace reactor {

Reactor::Reactor() : m_demux(), m_event_handlers(), m_closed() {}

Reactor::~Reactor() {
  clearClosedEventHandlers();

  for (std::size_t i = 0; i < m_event_handlers.size(); ++i)
    delete m_event_handlers[i];
}

IEventHandler *Reactor::getEventHandler(const int event_fd) const {
  if (event_fd < 0)
    return 0;
  const std::size_t fd = static_cast<std::size_t>(event_fd);
  if (fd >= m_event_handlers.size())
    return 0;
  return m_event_handlers[fd];
}

void Reactor::registerEventHandler(IEventHandler *event_handler,
                                   const int flag) {
  const int new_event_fd = event_handler->getHandlerFd();
  if (new_event_fd < 0)
    throw std::runtime_error("registerHandler: invalid new_event_fd");

  const std::size_t u_new_event_fd = static_cast<std::size_t>(new_event_fd);
  if (u_new_event_fd >= m_event_handlers.size()) {
    m_event_handlers.resize(u_new_event_fd + 1, NULL);
  }

  m_event_handlers[u_new_event_fd] = event_handler;

  if (!m_demux.add(new_event_fd, flag)) {
    m_event_handlers[u_new_event_fd] = 0;
    throw std::runtime_error("registerHandler: demultiplexer add failed");
  }
}

void Reactor::modifyEventFlag(const int fd, const int flag) {
  m_demux.modify(fd, flag);
}

void Reactor::removeEventHandler(const int fd) {
  IEventHandler *handler = getEventHandler(fd);
  if (!handler)
    return;

  m_demux.remove(fd);
  m_event_handlers[static_cast<std::size_t>(fd)] = 0;
  m_closed.push_back(handler);
}

void Reactor::run() {
  LOG("reactor loop starting");
  while (running) {
    const int n_events = m_demux.wait(-1);
    if (n_events < 0)
      continue;
    dispatch(n_events);
    clearClosedEventHandlers();
  }
  LOG("reactor run loop stopped");
}

void Reactor::dispatch(const int n_events) {
  for (int i = 0; i < n_events; ++i) {
    const int fd = m_demux.getEventFd(i);
    IEventHandler *handler = getEventHandler(fd);
    if (!handler)
      continue;

    if (m_demux.isError(i)) {
      removeEventHandler(fd);
      continue;
    }

    if (m_demux.isReadable(i)) {
      handler->onReadable(*this);
      handler = getEventHandler(fd);
      if (!handler)
        continue;
    }

    if (m_demux.isWritable(i))
      handler->onWritable(*this);
  }
}

void Reactor::clearClosedEventHandlers() {
  for (std::size_t i = 0; i < m_closed.size(); ++i)
    delete m_closed[i];
  m_closed.clear();
}

} // namespace reactor
} // namespace webserv
