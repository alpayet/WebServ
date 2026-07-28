#ifndef ICONNECTIONFACTORY_HPP
#define ICONNECTIONFACTORY_HPP

namespace webserv {
namespace handler {

class IEventHandler;

// Produces the per-connection event handler for a freshly accepted client fd.
class IConnectionFactory {
public:
  virtual ~IConnectionFactory() {}

  virtual IEventHandler *create(int client_fd) const = 0;
};

} // namespace handler
} // namespace webserv

#endif
