#ifndef TCPCONNECTIONFACTORY_HPP
#define TCPCONNECTIONFACTORY_HPP

#include "infrastructure/server/handler/IConnectionFactory.hpp"

namespace webserv {

	namespace appProtocol {
		class IProtocolFactory;
	} // namespace appProtocol

	namespace handler {

		class TcpConnectionFactory : public IConnectionFactory
		{
		public:
			explicit TcpConnectionFactory(appProtocol::IProtocolFactory* app_protocol_factory);
			~TcpConnectionFactory();

			IEventHandler* create(int client_fd) const;

		private:
			TcpConnectionFactory(const TcpConnectionFactory&);
			TcpConnectionFactory& operator=(const TcpConnectionFactory&);

			appProtocol::IProtocolFactory* m_app_protocol_factory;
		};

	} // namespace handler
} // namespace webserv

#endif
