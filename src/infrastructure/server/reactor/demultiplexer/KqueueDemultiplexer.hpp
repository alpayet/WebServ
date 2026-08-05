#ifndef KQUEUEDEMULTIPLEXER_HPP
#define KQUEUEDEMULTIPLEXER_HPP

#ifdef __APPLE__

#include <sys/event.h>

#include "infrastructure/server/reactor/demultiplexer/IEventDemultiplexer.hpp"
#include "infrastructure/storage/file_system/fd/Fd.hpp"

namespace webserv {
namespace reactor {

class KqueueDemultiplexer : public IEventDemultiplexer
{
  public:
	KqueueDemultiplexer();
	~KqueueDemultiplexer();

	bool add(int fd, int flag);
	bool modify(int fd, int flag);
	bool remove(int fd);

	int wait(int timeout_ms);

	int	 getEventFd(int index) const;
	bool isReadable(int index) const;
	bool isWritable(int index) const;
	bool isError(int index) const;

  private:
	KqueueDemultiplexer(KqueueDemultiplexer const &);
	KqueueDemultiplexer &operator=(KqueueDemultiplexer const &);

	bool apply(int fd, int flag);

	static int const KQ_MAX_EVENTS = 64;

	fd::Fd		  m_kqueue_fd;
	struct kevent m_events[KQ_MAX_EVENTS];
};

} // namespace reactor
} // namespace webserv

#endif

#endif
