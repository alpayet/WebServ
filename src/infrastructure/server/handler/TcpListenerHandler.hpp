#ifndef TCPLISTENERHANDLER_HPP
#define TCPLISTENERHANDLER_HPP

#include "infrastructure/server/handler/IEventHandler.hpp"
#include "infrastructure/storage/file_system/fd/Fd.hpp"

#include <ctime>

namespace webserv {

	namespace reactor {
		class Reactor;
	} // namespace reactor

	namespace handler {

		class IConnectionFactory;

		class TcpListenerHandler : public IEventHandler
		{
		public:
			TcpListenerHandler(int listen_fd, const IConnectionFactory& connection_factory);
			~TcpListenerHandler();

			int getFd() const;
			std::time_t getLastActivity() const;

			void onReadable(reactor::Reactor& reactor);
			void onWritable(reactor::Reactor& reactor);
			void onTimeout(reactor::Reactor& reactor);

		private:
			TcpListenerHandler(const TcpListenerHandler&);
			TcpListenerHandler& operator=(const TcpListenerHandler&);

			fd::Fd m_listener_fd;
			const IConnectionFactory& m_connection_factory;
		};

	} // namespace handler
} // namespace webserv

#endif
