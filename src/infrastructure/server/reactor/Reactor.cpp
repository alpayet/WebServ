#include "infrastructure/server/reactor/Reactor.hpp"

#include <csignal>
#include <cstddef>
#include <stdexcept>

#include "infrastructure/server/handler/IEventHandler.hpp"
#include "infrastructure/server/reactor/EventType.hpp"
#include "infrastructure/server/utils/Logger.hpp"
#include "infrastructure/server/utils/utils.hpp"

extern sig_atomic_t volatile g_running;

namespace webserv {
namespace reactor {

Reactor::Reactor() : m_demux(), m_event_handlers(), m_closed() {}

Reactor::~Reactor()
{
	clearClosedEventHandlers();

	for (std::size_t i = 0; i < m_event_handlers.size(); ++i)
		delete m_event_handlers[i];
}

handler::IEventHandler *Reactor::getEventHandler(int const event_fd) const
{
	if (event_fd < 0)
		return 0;

	std::size_t const fd = static_cast<std::size_t>(event_fd);
	if (fd >= m_event_handlers.size())
		return NULL;

	return m_event_handlers[fd];
}

bool Reactor::hasBeenClosed(int const fd) const
{
	for (std::size_t i = 0; i < m_closed.size(); ++i)
	{
		if (m_closed[i]->getFd() == fd)
			return true;
	}
	return false;
}

bool Reactor::addEventHandler(handler::IEventHandler *event_handler, int const flag)
{

	int const new_event_fd = event_handler->getFd();
	if (new_event_fd < 0)
	{
		delete event_handler;
		return false;
	}

	std::size_t const index = static_cast<std::size_t>(new_event_fd);

	try
	{
		if (index >= m_event_handlers.size())
			m_event_handlers.resize(index + 1, NULL);
	}
	catch (std::exception const &)
	{
		delete event_handler;
		return false;
	}

	if (!m_demux.add(new_event_fd, flag))
	{
		delete event_handler;
		return false;
	}

	m_event_handlers[index] = event_handler;
	return true;
}

void Reactor::modifyEventFlag(int const fd, int const flag) { m_demux.modify(fd, flag); }

void Reactor::removeEventHandler(int const fd)
{
	handler::IEventHandler *handler = getEventHandler(fd);
	if (!handler)
		return;

	m_demux.remove(fd);
	m_event_handlers[static_cast<std::size_t>(fd)] = 0;

	try
	{
		m_closed.push_back(handler);
	}
	catch (std::exception const &)
	{
		delete handler;
	}
}

void Reactor::run()
{
	Logger("reactor loop starting...");

	while (g_running)
	{
		int const n_events = m_demux.wait(-1);
		if (n_events > 0)
			dispatch(n_events);

		clearClosedEventHandlers();
	}
	Logger("reactor run loop stopped");
}

void Reactor::dispatch(int const n_events)
{
	for (int i = 0; i < n_events; ++i)
	{
		int const fd = m_demux.getEventFd(i);

		if (hasBeenClosed(fd))
			continue;

		handler::IEventHandler *handler = getEventHandler(fd);
		if (!handler)
			continue;

		if (m_demux.isError(i))
		{
			removeEventHandler(fd);
			continue;
		}

		try
		{
			if (m_demux.isReadable(i))
			{
				handler->onReadable(*this);
				handler = getEventHandler(fd);
				if (!handler)
					continue;
			}

			if (m_demux.isWritable(i))
				handler->onWritable(*this);
		}
		catch (std::exception const &e)
		{
			DEBUG("handler on fd " << fd << " throw, remove it: " << e.what());
			removeEventHandler(fd);
		}
	}
}

void Reactor::clearClosedEventHandlers()
{
	for (std::size_t i = 0; i < m_closed.size(); ++i)
		delete m_closed[i];
	m_closed.clear();
}

} // namespace reactor
} // namespace webserv
