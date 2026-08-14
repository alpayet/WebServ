#ifndef IENDPOINT_HPP
#define IENDPOINT_HPP

#include <stdexcept>
#include <string>

namespace webserv {

	namespace reactor {
		class Reactor;
	} // namespace reactor

	namespace transport {

		class IEndpoint
		{
		public:
			virtual ~IEndpoint() {}

			virtual void open(reactor::Reactor& reactor) = 0;

			virtual std::string formatEndpoint() const = 0;
		};

	} // namespace transport
} // namespace webserv

#endif
