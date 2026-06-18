#ifndef IPROTOCOLFACTORY_HPP
#define IPROTOCOLFACTORY_HPP

namespace webserv {
namespace protocol {

class IProtocol;

class IProtocolFactory {
public:
  virtual ~IProtocolFactory() {}

  virtual IProtocol *create() const = 0;
};

}
}

#endif
