#ifndef ENDPOINTEXCEPTION_HPP
#define ENDPOINTEXCEPTION_HPP

#include <stdexcept>
#include <string>

class EndpointException : public std::runtime_error {
public:
  explicit EndpointException(const std::string &what);
};

#endif // ENDPOINTEXCEPTION_HPP
