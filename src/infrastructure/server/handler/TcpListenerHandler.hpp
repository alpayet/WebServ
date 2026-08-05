#ifndef TCPLISTENERHANDLER_HPP
#define TCPLISTENERHANDLER_HPP

#include "infrastructure/server/handler/IEventHandler.hpp"
#include "infrastructure/storage/file_system/fd/Fd.hpp"

namespace webserv {

namespace reactor {
class Reactor;
}

namespace handler {

class IConnectionFactory;

class TcpListenerHandler : public IEventHandler
{
  public:
	TcpListenerHandler(int listen_fd, IConnectionFactory const &connection_factory);
	~TcpListenerHandler();

	int	 getFd() const;
	void onReadable(reactor::Reactor &reactor);
	void onWritable(reactor::Reactor &reactor);

  private:
	TcpListenerHandler(TcpListenerHandler const &);
	TcpListenerHandler &operator=(TcpListenerHandler const &);

	fd::Fd					  m_listener_fd;
	IConnectionFactory const &m_connection_factory;
};

} // namespace handler
} // namespace webserv

#endif
