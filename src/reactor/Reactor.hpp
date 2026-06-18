#ifndef REACTOR_HPP
#define REACTOR_HPP

#include <vector>

#include "reactor/demultiplexer/Demultiplexer.hpp"

namespace webserv {
namespace reactor {

class IEventHandler;

class Reactor {
public:
  Reactor();
  ~Reactor();

  void registerEventHandler(IEventHandler *event_handler, int flag);
  void modifyEventFlag(int fd, int flag);
  void removeEventHandler(int fd);

  void run();

private:
  Reactor(const Reactor &);
  Reactor &operator=(const Reactor &);

  IEventHandler *getEventHandler(int event_fd) const;
  void dispatch(int n_events);
  void clearClosedEventHandlers();

  Demultiplexer m_demux;
  std::vector<IEventHandler *> m_event_handlers;
  std::vector<IEventHandler *> m_closed;
};

} // namespace reactor
} // namespace webserv

#endif
