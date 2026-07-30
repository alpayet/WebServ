#include "HttpProtocolFactory.hpp"

#include "infrastructure/config/ServerConfig.hpp"
#include "server/protocol/HttpProtocol.hpp"

namespace webserv {
namespace protocol {

HttpProtocolFactory::HttpProtocolFactory(const ::ServerConfig &config) : _storage(), _directory_explorer(), _cgi(),
_serveStaticResourceUseCase(config, _storage, _directory_explorer), _deleteStaticResourceUseCase(config, _storage), _executeDynamicResourceUseCase(config, _cgi),
_serveStaticResourceController(_serveStaticResourceUseCase), _deleteStaticResourceController(_deleteStaticResourceUseCase), _executeDynamicResourceController(_executeDynamicResourceUseCase, config),
_requestParser(config, config), _cgiParser(config),
_router(config, _serveStaticResourceController, _deleteStaticResourceController),
_sender(config),
_handler(_requestParser, _cgiParser, _router, _sender, config) {
}

HttpProtocolFactory::~HttpProtocolFactory() {}

IProtocol *HttpProtocolFactory::create() { return new HttpProtocol(_handler);}

}
}
