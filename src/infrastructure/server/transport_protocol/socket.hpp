#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <cstddef>
#include <string>
#include <sys/socket.h>

namespace webserv {
	namespace transport {

		namespace socket {

			int createSocket(const std::string& host, int port, int socktype, std::string* family);

			int accept(int listen_fd);

			bool setNoDelay(int fd);

			ssize_t recv(int fd, char* buf, std::size_t len);
			ssize_t send(int fd, const char* buf, std::size_t len);

		} // namespace socket

	} // namespace transport
} // namespace webserv

#endif
