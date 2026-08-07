#ifndef ENDPOINTSET_HPP
#define ENDPOINTSET_HPP

#include <cstddef>
#include <vector>

namespace webserv {
namespace transport {

class IEndpoint;

class Endpoints {
public:
  Endpoints();
  ~Endpoints();

  void add(IEndpoint *endpoint);

  std::size_t size() const;
  IEndpoint &operator[](std::size_t index) const;

private:
  Endpoints(const Endpoints &);
  Endpoints &operator=(const Endpoints &);

  std::vector<IEndpoint *> m_endpoints;
};

} // namespace transport
} // namespace webserv

#endif
