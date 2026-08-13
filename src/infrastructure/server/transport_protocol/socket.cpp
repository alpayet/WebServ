#include "infrastructure/server/transport_protocol/socket.hpp"

#include <cstring>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include <stdexcept>

#include "infrastructure/server/utils/utils.hpp"
#include "infrastructure/storage/file_system/fd/Fd.hpp"

namespace webserv {
    namespace transport {
        namespace socket {

            static char const* detectSockaddrFamily(const struct sockaddr* sa)
            {
                if (sa == 0)
                    return "";

                switch (sa->sa_family)
                {
                case AF_INET:
                    return "ipv4";
                case AF_INET6:
                    return "ipv6";
                default:
                    return "unknown_af";
                }
            }

            int createSocket(std::string const& host, int const port, int const socktype, std::string* family)
            {
                addrinfo hints = {};
                std::memset(&hints, 0, sizeof(hints));
                hints.ai_flags = AI_PASSIVE;
                hints.ai_family = AF_UNSPEC;
                hints.ai_socktype = socktype;

                addrinfo* info = 0;
                int const status = getaddrinfo(host.c_str(), ft::intToString(port).c_str(), &hints, &info);
                if (status != 0)
                    throw std::runtime_error(gai_strerror(status));

                addrinfo const* p = 0;
                fd::Fd tmp_fd;
                int const yes = 1;

                for (p = info; p != 0; p = p->ai_next)
                {
                    tmp_fd.reset(::socket(p->ai_family, p->ai_socktype, p->ai_protocol));

                    if (tmp_fd.get() == -1)
                        continue;

                    ::fcntl(tmp_fd.get(), F_SETFD, FD_CLOEXEC);

                    if (setsockopt(tmp_fd.get(), SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
                        continue;

                    if (bind(tmp_fd.get(), p->ai_addr, p->ai_addrlen) == -1)
                        continue;

                    break;
                }

                if (p != 0 && family != 0)
                    *family = detectSockaddrFamily(p->ai_addr);

                freeaddrinfo(info);

                if (p == 0)
                    throw std::runtime_error("bind failed for " + host + ":" + ft::intToString(port));
                return tmp_fd.release();
            }

            int accept(int const listen_fd)
            {
                const int fd = ::accept(listen_fd, 0, 0);
                if (fd != -1)
                    ::fcntl(fd, F_SETFD, FD_CLOEXEC);
                return fd;
            }

            bool setNoDelay(const int fd)
            {
                const int yes = 1;
                return setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &yes, sizeof(yes)) != -1;
            }

            ssize_t recv(int const fd, char* buf, std::size_t const len) { return ::recv(fd, buf, len, 0); }

            ssize_t send(int const fd, char const* buf, std::size_t const len) { return ::send(fd, buf, len, 0); }

        } // namespace socket
    } // namespace transport
} // namespace webserv
