#include "infrastructure/server/reactor/demultiplexer/KqueueDemultiplexer.hpp"

#ifdef __APPLE__

#include <stdexcept>
#include <stdint.h>

#include "infrastructure/server/reactor/EventType.hpp"
#include "infrastructure/server/utils/Logger.hpp"

namespace webserv {
namespace reactor {

KqueueDemultiplexer::KqueueDemultiplexer() : m_kqueue_fd(kqueue()), m_events()
{
	if (m_kqueue_fd.get() == -1)
		throw std::runtime_error("kqueue() failed");
	std::memset(m_events, 0, sizeof(m_events));
	DEBUG("kqueue demultiplexer ready, fd: " << m_kqueue_fd.get());
}

KqueueDemultiplexer::~KqueueDemultiplexer() {}

bool KqueueDemultiplexer::apply(int const fd, int const flag)
{
	struct kevent	changes[2];
	uintptr_t const ident = static_cast<uintptr_t>(fd);

	unsigned short const read_flag =
		static_cast<unsigned short>(EV_ADD | ((flag & EVENT_READ) ? EV_ENABLE : EV_DISABLE));

	unsigned short const write_flag =
		static_cast<unsigned short>(EV_ADD | ((flag & EVENT_WRITE) ? EV_ENABLE : EV_DISABLE));

	EV_SET(&changes[0], ident, EVFILT_READ, read_flag, 0, 0, 0);
	EV_SET(&changes[1], ident, EVFILT_WRITE, write_flag, 0, 0, 0);

	return kevent(m_kqueue_fd.get(), changes, 2, 0, 0, 0) != -1;
}

bool KqueueDemultiplexer::add(int const fd, int const flag)
{
	DEBUG("kqueue add fd: " << fd << " flag: " << flag);
	return apply(fd, flag);
}

bool KqueueDemultiplexer::modify(int const fd, int const flag)
{
	DEBUG("kqueue modify fd: " << fd << " flag: " << flag);
	return apply(fd, flag);
}

bool KqueueDemultiplexer::remove(int const fd)
{
	DEBUG("kqueue remove fd: " << fd);
	struct kevent	changes[2];
	uintptr_t const ident = static_cast<uintptr_t>(fd);

	EV_SET(&changes[0], ident, EVFILT_READ, EV_DELETE, 0, 0, 0);
	EV_SET(&changes[1], ident, EVFILT_WRITE, EV_DELETE, 0, 0, 0);

	return kevent(m_kqueue_fd.get(), changes, 2, 0, 0, 0) != -1;
}

int KqueueDemultiplexer::wait(int const timeout_ms)
{
	(void)timeout_ms;

	return kevent(m_kqueue_fd.get(), 0, 0, m_events, KQ_MAX_EVENTS, 0);
}

int KqueueDemultiplexer::getEventFd(int const index) const
{
	return static_cast<int>(m_events[index].ident);
}

bool KqueueDemultiplexer::isReadable(int const index) const
{
	return m_events[index].filter == EVFILT_READ;
}

bool KqueueDemultiplexer::isWritable(int const index) const
{
	return m_events[index].filter == EVFILT_WRITE;
}

bool KqueueDemultiplexer::isError(int const index) const
{
	return (m_events[index].flags & EV_ERROR) != 0;
}

} // namespace reactor
} // namespace webserv

#endif
