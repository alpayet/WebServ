#ifndef TCPTRANSPORT_HPP
#define TCPTRANSPORT_HPP

#include "infrastructure/server/transport_protocol/ITransport.hpp"
#include "infrastructure/storage/file_system/fd/Fd.hpp"

namespace webserv {
	namespace transport {

		class TcpTransport : public ITransport
		{
		public:
			explicit TcpTransport(int fd);
			~TcpTransport();

			int getFd() const;
			ssize_t read(char* buf, std::size_t len);
			ssize_t write(const char* buf, std::size_t len);

		private:
			TcpTransport(const TcpTransport&);
			TcpTransport& operator=(const TcpTransport&);

			fd::Fd m_fd;
		};

	} // namespace transport
} // namespace webserv

#endif
