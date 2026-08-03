#include "server/transport_protocol/endpoint/Endpoints.hpp"

#include "server/transport_protocol/endpoint/IEndpoint.hpp"

namespace webserv {
namespace transport {

Endpoints::Endpoints() : m_endpoints() {}

Endpoints::~Endpoints() {
  for (std::size_t i = 0; i < m_endpoints.size(); ++i)
    delete m_endpoints[i];
}

void Endpoints::add(IEndpoint *endpoint) {
  try {
    m_endpoints.push_back(endpoint);
  } catch (...) {
    delete endpoint;
    throw;
  }
}

std::size_t Endpoints::size() const { return m_endpoints.size(); }

IEndpoint &Endpoints::operator[](const std::size_t index) const {
  return *m_endpoints[index];
}

} // namespace transport
} // namespace webserv
