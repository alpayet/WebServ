#ifndef TESTPROTOCOL_HPP
#define TESTPROTOCOL_HPP

#include <string>
#include <vector>

#include "application/ports/IDynamicResourceExecutor.hpp"
#include "infrastructure/server/application_protocol/IProtocol.hpp"
#include "infrastructure/server/application_protocol/IProtocolFactory.hpp"

namespace webserv {
	namespace appProtocol {

		class TestProtocol : public IProtocol
		{
		public:
			explicit TestProtocol(const std::string& body);
			~TestProtocol();

			PushStatus::Type pushRequest(const char* inputBuf, std::size_t size, RequestStatus::Type status);
			PushStatus::Type pushStream(const char* streamBuf, std::size_t size, StreamStatus::Type status);

			PullStatus::Type pullResponse(std::vector<char>& outputBuf);

			app::StreamInfo getStreamResources() const;

			void reset();

			bool shouldKeepAlive() const;

		private:
			TestProtocol(const TestProtocol&);
			TestProtocol& operator=(const TestProtocol&);

			std::string m_request;
			std::vector<char> m_response;
		};

		class TestProtocolFactory : public IProtocolFactory
		{
		public:
			explicit TestProtocolFactory(const std::string& body);
			~TestProtocolFactory();

			IProtocol* create();

		private:
			std::string m_body;
		};

	} // namespace appProtocol
} // namespace webserv

#endif
