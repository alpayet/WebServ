#ifndef IPROTOCOLFACTORY_HPP
#define IPROTOCOLFACTORY_HPP

namespace webserv {
	namespace appProtocol {

		class IProtocol;

		class IProtocolFactory
		{
		public:
			virtual ~IProtocolFactory() {}

			virtual IProtocol* create() = 0;
		};

	} // namespace appProtocol
} // namespace webserv

#endif
