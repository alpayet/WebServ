#include "infrastructure/server/handler/TcpListenerHandler.hpp"

#include "infrastructure/server/handler/IConnectionFactory.hpp"
#include "infrastructure/server/reactor/EventType.hpp"
#include "infrastructure/server/reactor/Reactor.hpp"
#include "infrastructure/server/transport_protocol/socket.hpp"
#include "infrastructure/server/utils/utils.hpp"

namespace webserv {
	namespace handler {

		TcpListenerHandler::TcpListenerHandler(const int listen_fd, const IConnectionFactory& connection_factory) :
		    m_listener_fd(listen_fd), m_connection_factory(connection_factory)
		{}

		TcpListenerHandler::~TcpListenerHandler() {}

		int TcpListenerHandler::getFd() const { return m_listener_fd.get(); }

		void TcpListenerHandler::onWritable(reactor::Reactor&) {}

		void TcpListenerHandler::onReadable(reactor::Reactor& reactor)
		{
			for (;;)
			{
				const int client_fd = transport::socket::accept(m_listener_fd.get());

				if (client_fd < 0)
					return;

				fd::Fd tmp_fd(client_fd);

				if (!tmp_fd.setNonBlocking())
					continue;


				transport::socket::setNoDelay(tmp_fd.get());

				try
				{
					IEventHandler* handler = m_connection_factory.create(tmp_fd.release());

					reactor.addEventHandler(handler, reactor::EVENT_READ);
				}
				catch (...)
				{}

				// LOG("accepted client fd: " << client_fd);
			}
		}

		void TcpListenerHandler::onTimeout(reactor::Reactor& reactor)
		{
			reactor.removeEventHandler(m_listener_fd.get());
		}

		std::time_t TcpListenerHandler::getLastActivity() const { return -1; }

	} // namespace handler
} // namespace webserv
