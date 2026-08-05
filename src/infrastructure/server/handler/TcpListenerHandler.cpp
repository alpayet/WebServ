#include "infrastructure/server/handler/TcpListenerHandler.hpp"

#include "infrastructure/server/handler/IConnectionFactory.hpp"
#include "infrastructure/server/reactor/EventType.hpp"
#include "infrastructure/server/reactor/Reactor.hpp"
#include "infrastructure/server/transport_protocol/socket.hpp"
#include "infrastructure/server/utils/Logger.hpp"
#include "infrastructure/server/utils/utils.hpp"

namespace webserv {
namespace handler {

TcpListenerHandler::TcpListenerHandler(
	int const listen_fd, IConnectionFactory const &connection_factory
)
	: m_listener_fd(listen_fd), m_connection_factory(connection_factory)
{}

TcpListenerHandler::~TcpListenerHandler() {}

int TcpListenerHandler::getFd() const { return m_listener_fd.get(); }

void TcpListenerHandler::onWritable(reactor::Reactor &) {}

void TcpListenerHandler::onReadable(reactor::Reactor &reactor)
{

	for (;;)
	{
		int const client_fd = transport::socket::accept(m_listener_fd.get());

		if (client_fd < 0)
			return;

		fd::Fd tmp_fd(client_fd);

		if (!tmp_fd.setNonBlocking())
		{
			DEBUG("can't set fd " << client_fd << " non-blocking so delete it");
			continue;
		}

		try
		{
			IEventHandler *handler = m_connection_factory.create(tmp_fd.release());

			reactor.addEventHandler(handler, reactor::EVENT_READ);
		}
		catch (std::exception const &e)
		{
			DEBUG(
				"can't add new client after accept, remove client fd: " << client_fd << ": "
																		<< e.what()
			);
		}

		// LOG("accepted client fd: " << client_fd);
	}
}

} // namespace handler
} // namespace webserv
