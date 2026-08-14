#include "infrastructure/server/reactor/Reactor.hpp"

#include "infrastructure/server/handler/ConnectionHandler.hpp"

#include <csignal>
#include <cstddef>
#include <stdexcept>

#include "infrastructure/server/handler/IEventHandler.hpp"
#include "infrastructure/server/reactor/EventType.hpp"
#include "infrastructure/server/utils/Logger.hpp"
#include "infrastructure/server/utils/utils.hpp"

extern volatile sig_atomic_t g_running;

namespace webserv {
	namespace reactor {

		Reactor::Reactor() {}

		Reactor::~Reactor()
		{
			clearClosedEventHandlers();

			for (std::size_t i = 0; i < m_event_handlers.size(); ++i) delete m_event_handlers[i];
		}

		handler::IEventHandler* Reactor::getEventHandler(const int event_fd) const
		{
			if (event_fd < 0)
				return 0;

			const std::size_t fd = static_cast<std::size_t>(event_fd);
			if (fd >= m_event_handlers.size())
				return NULL;

			return m_event_handlers[fd];
		}

		bool Reactor::hasBeenClosed(const int fd) const
		{
			for (std::size_t i = 0; i < m_closed.size(); ++i)
			{
				if (m_closed[i]->getFd() == fd)
					return true;
			}
			return false;
		}

		bool Reactor::addEventHandler(handler::IEventHandler* event_handler, const int flag)
		{
			const int new_event_fd = event_handler->getFd();
			if (new_event_fd < 0)
			{
				delete event_handler;
				return false;
			}

			const std::size_t index = static_cast<std::size_t>(new_event_fd);

			try
			{
				if (index >= m_event_handlers.size())
					m_event_handlers.resize(index + 1, NULL);
			}
			catch (...)
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

		void Reactor::modifyEventFlag(const int fd, const int flag) { m_demux.modify(fd, flag); }

		void Reactor::removeEventHandler(const int fd)
		{
			handler::IEventHandler* handler = getEventHandler(fd);
			if (!handler)
				return;

			m_demux.remove(fd);
			m_event_handlers[static_cast<std::size_t>(fd)] = 0;

			try
			{
				m_closed.push_back(handler);
			}
			catch (...)
			{
				delete handler;
			}
		}

		void Reactor::releaseFromDemux(const int fd) { m_demux.remove(fd); }

		void Reactor::backToDemux(const int fd, const int flag) { m_demux.add(fd, flag); }

		int Reactor::computePollTimeout() const
		{
			const std::time_t now = ft::now();
			std::time_t next_timeout = 0;
			bool need_timeout = false;

			for (std::size_t i = 0; i < m_event_handlers.size(); ++i)
			{
				const handler::IEventHandler* handler = getEventHandler(i);
				if (!handler)
					continue;

				const std::time_t last_activity = handler->getLastActivity();
				if (last_activity == -1)
					continue;

				const std::time_t soon = last_activity + IDLE_CONNECTION_TIMEOUT_S - now;

				if (!need_timeout || soon < next_timeout)
				{
					need_timeout = true;
					next_timeout = soon;
				}
			}
			if (!need_timeout)
				return -1;
			if (next_timeout < 0)
				return 0;
			return next_timeout * 1000;
		}

		void Reactor::expireIdleConnections()
		{
			const std::time_t now = ft::now();

			for (std::size_t i = 0; i < m_event_handlers.size(); ++i)
			{
				handler::IEventHandler* handler = getEventHandler(static_cast<int>(i));
				if (!handler || hasBeenClosed(handler->getFd()))
					continue;

				const std::time_t last_activity = handler->getLastActivity();
				if (last_activity == -1)
					continue;

				if (now - last_activity >= IDLE_CONNECTION_TIMEOUT_S)
					handler->onTimeout(*this);
			}
		}

		void Reactor::run()
		{
			Logger("reactor loop starting...");

			std::time_t last_metrics = ft::now();

			while (g_running)
			{
				const int n_events = m_demux.wait(computePollTimeout());
				if (n_events > 0)
					dispatch(n_events);
				expireIdleConnections();
				const std::time_t now = ft::now();
				if (now - last_metrics >= 3)
				{
					logMetrics();
					last_metrics = now;
				}
				clearClosedEventHandlers();
			}
			Logger("reactor run loop stopped");
		}

		void Reactor::dispatch(const int n_events)
		{
			for (int i = 0; i < n_events; ++i)
			{
				const int fd = m_demux.getEventFd(i);

				if (hasBeenClosed(fd))
					continue;

				handler::IEventHandler* handler = getEventHandler(fd);
				if (!handler)
					continue;

				try
				{
					if (m_demux.isReadable(i) || m_demux.isError(i))
						handler->onReadable(*this);

					if (m_demux.isWritable(i))
						handler->onWritable(*this);
				}
				catch (...)
				{
					removeEventHandler(fd);
				}
			}
		}

		void Reactor::clearClosedEventHandlers()
		{
			for (std::size_t i = 0; i < m_closed.size(); ++i) delete m_closed[i];

			m_closed.clear();
		}

		void Reactor::logMetrics() const
		{
			const double rps = handler::ConnectionHandler::n_complete_requests / 3;

			LOG("metrics: active=" << handler::ConnectionHandler::n_active_connections
			                       << " req/3s=" << handler::ConnectionHandler::n_complete_requests << " rps=" << rps);

			handler::ConnectionHandler::n_complete_requests = 0;
		}

	} // namespace reactor
} // namespace webserv
