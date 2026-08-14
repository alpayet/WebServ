#include "infrastructure/server/reactor/demultiplexer/KqueueDemultiplexer.hpp"

#ifdef __APPLE__

#include <stdexcept>
#include <stdint.h>
#include <sys/time.h>

#include "infrastructure/server/reactor/EventType.hpp"
#include "infrastructure/server/utils/Logger.hpp"

namespace webserv {
	namespace reactor {

		KqueueDemultiplexer::KqueueDemultiplexer() : m_kqueue_fd(kqueue()), m_events()
		{
			if (m_kqueue_fd.get() == -1)
				throw std::runtime_error("kqueue() failed");
			std::memset(m_events, 0, sizeof(m_events));
		}

		KqueueDemultiplexer::~KqueueDemultiplexer() {}

		bool KqueueDemultiplexer::apply(const int fd, const int flag)
		{
			struct kevent changes[2];
			const uintptr_t ident = static_cast<uintptr_t>(fd);

			const unsigned short read_flag =
			    static_cast<unsigned short>(EV_ADD | ((flag & EVENT_READ) ? EV_ENABLE : EV_DISABLE));

			const unsigned short write_flag =
			    static_cast<unsigned short>(EV_ADD | ((flag & EVENT_WRITE) ? EV_ENABLE : EV_DISABLE));

			EV_SET(&changes[0], ident, EVFILT_READ, read_flag, 0, 0, 0);
			EV_SET(&changes[1], ident, EVFILT_WRITE, write_flag, 0, 0, 0);

			return kevent(m_kqueue_fd.get(), changes, 2, 0, 0, 0) != -1;
		}

		bool KqueueDemultiplexer::add(const int fd, const int flag) { return apply(fd, flag); }

		bool KqueueDemultiplexer::modify(const int fd, const int flag) { return apply(fd, flag); }

		bool KqueueDemultiplexer::remove(const int fd)
		{
			struct kevent changes[2];
			const uintptr_t ident = static_cast<uintptr_t>(fd);

			EV_SET(&changes[0], ident, EVFILT_READ, EV_DELETE, 0, 0, 0);
			EV_SET(&changes[1], ident, EVFILT_WRITE, EV_DELETE, 0, 0, 0);

			return kevent(m_kqueue_fd.get(), changes, 2, 0, 0, 0) != -1;
		}

		int KqueueDemultiplexer::wait(const int timeout_ms)
		{
			const struct timespec* ts = NULL;
			struct timespec ts1;

			if (timeout_ms >= 0)
			{
				ts1.tv_sec = timeout_ms / 1000;
				ts1.tv_nsec = (timeout_ms % 1000) * 1000000;
				ts = &ts1;
			}

			return kevent(m_kqueue_fd.get(), 0, 0, m_events, KQ_MAX_EVENTS, ts);
		}

		int KqueueDemultiplexer::getEventFd(const int index) const { return static_cast<int>(m_events[index].ident); }

		bool KqueueDemultiplexer::isReadable(const int index) const { return m_events[index].filter == EVFILT_READ; }

		bool KqueueDemultiplexer::isWritable(const int index) const { return m_events[index].filter == EVFILT_WRITE; }

		bool KqueueDemultiplexer::isError(const int index) const { return (m_events[index].flags & EV_ERROR) != 0; }

	} // namespace reactor
} // namespace webserv

#endif
