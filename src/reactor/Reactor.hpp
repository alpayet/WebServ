#ifndef REACTOR_HPP
#define REACTOR_HPP

#include <vector>

#include "reactor/demultiplexer/Demultiplexer.hpp"

namespace webserv {

namespace handler {
class IEventHandler;
}

namespace reactor {

class Reactor {
public:
  Reactor();
  ~Reactor();

  bool addEventHandler(handler::IEventHandler *event_handler, int flag);
  void removeEventHandler(int fd);

  void modifyEventFlag(int fd, int flag);

  void run();

private:
  Reactor(const Reactor &);
  Reactor &operator=(const Reactor &);

  handler::IEventHandler *getEventHandler(int event_fd) const;
  void dispatch(int n_events);
  bool hasBeenClosed(int fd) const;
  void clearClosedEventHandlers();

  Demultiplexer m_demux;
  std::vector<handler::IEventHandler *> m_event_handlers;
  std::vector<handler::IEventHandler *> m_closed;
};

} // namespace reactor
} // namespace webserv

#endif
