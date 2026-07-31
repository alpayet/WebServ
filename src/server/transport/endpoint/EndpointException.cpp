#include "server/transport/endpoint/EndpointException.hpp"

EndpointException::EndpointException(const std::string &what)
    : std::runtime_error("Endpoint error: " + what) {}