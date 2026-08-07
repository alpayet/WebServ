#ifndef HTTPSESSION_HPP
#define HTTPSESSION_HPP

#include "infrastructure/server/application_protocol/IProtocol.hpp"
#include "infrastructure/server/application_protocol/http/core/Context.hpp"

namespace http {
class Protocol;

class Session : public webserv::appProtocol::IProtocol
{
  public:
	Session(Protocol &handler);
	virtual ~Session() {}

	virtual PushStatus pushRequest(std::vector<char> const &inputBuf, RequestStatus::Type status);
	virtual PushStatus pushStream(std::vector<char> const &streamBuf, StreamStatus::Type status);

	virtual PullStatus pullResponse(std::vector<char> &outputBuf);

	virtual void reset(void);

	virtual bool shouldKeepAlive(void) const;

  private:
	Session(Session const &);
	Session &operator=(Session const &);

	http::Context	_context;
	http::Protocol &_protocol;
};

} // namespace http

#endif // HTTPSESSION_HPP
