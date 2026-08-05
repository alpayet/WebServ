#include "infrastructure/server/application_protocol/http/ProtocolFactory.hpp"
#include "infrastructure/config/ServerConfig.hpp"
#include "infrastructure/server/application_protocol/http/Session.hpp"
#include "infrastructure/server/utils/Logger.hpp"

namespace http {

ProtocolFactory::ProtocolFactory(ServerConfig const &config)
	: _storage(), _directory_explorer(), _cgi(),
	  _serveStaticResourceUseCase(config, _storage, _directory_explorer),
	  _deleteStaticResourceUseCase(config, _storage), _executeDynamicResourceUseCase(config, _cgi),
	  _serveStaticResourceController(_serveStaticResourceUseCase),
	  _deleteStaticResourceController(_deleteStaticResourceUseCase),
	  _executeDynamicResourceController(_executeDynamicResourceUseCase, config),
	  _requestParser(config, config), _cgiParser(config),
	  _router(config, _serveStaticResourceController, _deleteStaticResourceController),
	  _sender(config), _protocol(_requestParser, _cgiParser, _router, _sender, config)
{}

ProtocolFactory::~ProtocolFactory() {}

webserv::appProtocol::IProtocol *ProtocolFactory::create() { return new Session(_protocol); }

} // namespace http
