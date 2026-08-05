#ifndef REACTOR_HPP
#define REACTOR_HPP

#include <vector>

#include "infrastructure/server/reactor/demultiplexer/Demultiplexer.hpp"

namespace webserv {

namespace handler {
class IEventHandler;
}

namespace reactor {

class Reactor
{
  public:
	Reactor();
	~Reactor();

	bool addEventHandler(handler::IEventHandler *event_handler, int flag);
	void removeEventHandler(int fd);

	void modifyEventFlag(int fd, int flag);

	void run();

  private:
	Reactor(Reactor const &);
	Reactor &operator=(Reactor const &);

	handler::IEventHandler *getEventHandler(int event_fd) const;
	void					dispatch(int n_events);
	bool					hasBeenClosed(int fd) const;
	void					clearClosedEventHandlers();

	Demultiplexer						  m_demux;
	std::vector<handler::IEventHandler *> m_event_handlers;
	std::vector<handler::IEventHandler *> m_closed;
};

} // namespace reactor
} // namespace webserv

#endif
