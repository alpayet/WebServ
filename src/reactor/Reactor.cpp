#include "reactor/Reactor.hpp"

#include <csignal>
#include <cstddef>
#include <stdexcept>

#include "handler/IEventHandler.hpp"
#include "reactor/EventType.hpp"
#include "utils/Logger.hpp"
#include "utils/utils.hpp"

extern volatile sig_atomic_t g_running;

namespace webserv {
namespace reactor {

Reactor::Reactor() : m_demux(), m_event_handlers(), m_closed() {}

Reactor::~Reactor() {
  clearClosedEventHandlers();

  for (std::size_t i = 0; i < m_event_handlers.size(); ++i)
    delete m_event_handlers[i];
}

handler::IEventHandler *Reactor::getEventHandler(const int event_fd) const {
  if (event_fd < 0)
    return 0;

  const std::size_t fd = static_cast<std::size_t>(event_fd);
  if (fd >= m_event_handlers.size())
    return NULL;

  return m_event_handlers[fd];
}

bool Reactor::hasBeenClosed(const int fd) const {
  for (std::size_t i = 0; i < m_closed.size(); ++i) {
    if (m_closed[i]->getFd() == fd)
      return true;
  }
  return false;
}

bool Reactor::addEventHandler(handler::IEventHandler *event_handler,
                              const int flag) {

  const int new_event_fd = event_handler->getFd();
  if (new_event_fd < 0) {
    delete event_handler;
    return false;
  }

  const std::size_t index = static_cast<std::size_t>(new_event_fd);

  try {
    if (index >= m_event_handlers.size())
      m_event_handlers.resize(index + 1, NULL);
  } catch (const std::exception &) {
    delete event_handler;
    return false;
  }

  if (!m_demux.add(new_event_fd, flag)) {
    delete event_handler;
    return false;
  }

  m_event_handlers[index] = event_handler;
  return true;
}

void Reactor::modifyEventFlag(const int fd, const int flag) {
  m_demux.modify(fd, flag);
}

void Reactor::removeEventHandler(const int fd) {
  handler::IEventHandler *handler = getEventHandler(fd);
  if (!handler)
    return;

  m_demux.remove(fd);
  m_event_handlers[static_cast<std::size_t>(fd)] = 0;

  try {
    m_closed.push_back(handler);
  } catch (const std::exception &) {
    delete handler;
  }
}

void Reactor::run() {
  LOG("reactor loop starting...");

  while (g_running) {
    const int n_events = m_demux.wait(-1);
    if (n_events > 0)
      dispatch(n_events);

    clearClosedEventHandlers();
  }
  LOG("reactor run loop stopped");
}

void Reactor::dispatch(const int n_events) {
  for (int i = 0; i < n_events; ++i) {
    const int fd = m_demux.getEventFd(i);

    if (hasBeenClosed(fd))
      continue;

    handler::IEventHandler *handler = getEventHandler(fd);
    if (!handler)
      continue;

    if (m_demux.isError(i)) {
      removeEventHandler(fd);
      continue;
    }

    try {
      if (m_demux.isReadable(i)) {
        handler->onReadable(*this);
        handler = getEventHandler(fd);
        if (!handler)
          continue;
      }

      if (m_demux.isWritable(i))
        handler->onWritable(*this);
    } catch (const std::exception &e) {
      DEBUG("handler on fd " << fd << " throw, remove it: " << e.what());
      removeEventHandler(fd);
    }
  }
}

void Reactor::clearClosedEventHandlers() {
  for (std::size_t i = 0; i < m_closed.size(); ++i)
    delete m_closed[i];
  m_closed.clear();
}

} // namespace reactor
} // namespace webserv
