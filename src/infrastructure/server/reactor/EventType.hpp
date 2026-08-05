#ifndef EVENTTYPE_HPP
#define EVENTTYPE_HPP

namespace webserv {
namespace reactor {

enum EventType { EVENT_NONE = 0, EVENT_READ = 1 << 0, EVENT_WRITE = 1 << 1 };

}
} // namespace webserv

#endif
