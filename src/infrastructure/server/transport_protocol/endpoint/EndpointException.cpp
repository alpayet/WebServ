#include "infrastructure/server/transport_protocol/endpoint/EndpointException.hpp"

EndpointException::EndpointException(std::string const &what)
	: std::runtime_error("Endpoint error: " + what)
{}