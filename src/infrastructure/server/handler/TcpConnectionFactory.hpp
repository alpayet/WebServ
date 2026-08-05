#ifndef TCPCONNECTIONFACTORY_HPP
#define TCPCONNECTIONFACTORY_HPP

#include "infrastructure/server/handler/IConnectionFactory.hpp"

namespace webserv {

namespace appProtocol {
class IProtocolFactory;
}

namespace handler {

class TcpConnectionFactory : public IConnectionFactory
{
  public:
	explicit TcpConnectionFactory(appProtocol::IProtocolFactory *app_protocol_factory);
	~TcpConnectionFactory();

	IEventHandler *create(int client_fd) const;

  private:
	TcpConnectionFactory(TcpConnectionFactory const &);
	TcpConnectionFactory &operator=(TcpConnectionFactory const &);

	appProtocol::IProtocolFactory *m_app_protocol_factory;
};

} // namespace handler
} // namespace webserv

#endif
