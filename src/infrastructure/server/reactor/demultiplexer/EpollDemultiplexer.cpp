#include "infrastructure/server/reactor/demultiplexer/EpollDemultiplexer.hpp"

#ifdef __linux__

#include <cstring>
#include <stdexcept>

#include <fcntl.h>
#include "infrastructure/server/reactor/EventType.hpp"
#include "infrastructure/server/utils/Logger.hpp"

namespace webserv {
    namespace reactor {

        uint32_t getEpollMask(int const flag)
        {
            uint32_t mask = 0;
            if (flag & EVENT_READ)
                mask |= EPOLLIN;
            if (flag & EVENT_WRITE)
                mask |= EPOLLOUT;
            return mask;
        }

        EpollDemultiplexer::EpollDemultiplexer() : m_epoll_fd(epoll_create(1)), m_events()
        {
            if (m_epoll_fd.get() == -1)
                throw std::runtime_error("epoll_create() failed");

            ::fcntl(m_epoll_fd.get(), F_SETFD, FD_CLOEXEC);

            std::memset(m_events, 0, sizeof(m_events));

            DEBUG("epoll demultiplexer ready, fd: " << m_epoll_fd.get());
        }

        EpollDemultiplexer::~EpollDemultiplexer() {}

        bool EpollDemultiplexer::add(int const fd, int const flag)
        {
            struct epoll_event ev;
            std::memset(&ev, 0, sizeof(ev));
            ev.events = getEpollMask(flag);
            ev.data.fd = fd;
            std::string const s(flag & EVENT_WRITE ? "write" : flag & EVENT_READ ? "read" : "none");
            DEBUG("epoll add fd: " << fd << " flag: " << s);
            return epoll_ctl(m_epoll_fd.get(), EPOLL_CTL_ADD, fd, &ev) != -1;
        }

        bool EpollDemultiplexer::modify(int const fd, int const flag)
        {
            struct epoll_event ev;
            std::memset(&ev, 0, sizeof(ev));
            ev.events = getEpollMask(flag);
            ev.data.fd = fd;
            std::string const s(flag & EVENT_WRITE ? "write" : flag & EVENT_READ ? "read" : "none");
            DEBUG("epoll modify fd: " << fd << " flag: " << s);
            return epoll_ctl(m_epoll_fd.get(), EPOLL_CTL_MOD, fd, &ev) != -1;
        }

        bool EpollDemultiplexer::remove(int const fd)
        {
            DEBUG("epoll remove fd: " << fd);
            return epoll_ctl(m_epoll_fd.get(), EPOLL_CTL_DEL, fd, 0) != -1;
        }

        int EpollDemultiplexer::wait(int const timeout_ms)
        {
            return epoll_wait(m_epoll_fd.get(), m_events, EPOLL_MAX_EVENTS, timeout_ms);
        }

        int EpollDemultiplexer::getEventFd(int const index) const { return m_events[index].data.fd; }

        bool EpollDemultiplexer::isReadable(int const index) const { return (m_events[index].events & EPOLLIN) != 0; }

        bool EpollDemultiplexer::isWritable(int const index) const { return (m_events[index].events & EPOLLOUT) != 0; }

        bool EpollDemultiplexer::isError(int const index) const
        {
            return (m_events[index].events & (EPOLLERR | EPOLLHUP)) != 0;
        }

    } // namespace reactor
} // namespace webserv

#endif
