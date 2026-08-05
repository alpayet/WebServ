#ifndef ICONNECTIONFACTORY_HPP
#define ICONNECTIONFACTORY_HPP

namespace webserv {
namespace handler {

class IEventHandler;

class IConnectionFactory {
public:
  virtual ~IConnectionFactory() {}

  virtual IEventHandler *create(int client_fd) const = 0;
};

} // namespace handler
} // namespace webserv

#endif
