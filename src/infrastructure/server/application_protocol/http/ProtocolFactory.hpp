#ifndef HTTPPROTOCOLFACTORY_HPP
#define HTTPPROTOCOLFACTORY_HPP

#include "application/use_cases/delete_static_resource/DeleteStaticResource.hpp"
#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.hpp"
#include "application/use_cases/serve_static_resource/ServeStaticResource.hpp"
#include "cgi/Cgi.hpp"
#include "infrastructure/server/application_protocol/IProtocolFactory.hpp"
#include "infrastructure/server/application_protocol/http/controllers/DeleteStaticResourceController.hpp"
#include "infrastructure/server/application_protocol/http/controllers/ExecuteDynamicResourceController.hpp"
#include "infrastructure/server/application_protocol/http/controllers/ServeStaticResourceController.hpp"
#include "infrastructure/server/application_protocol/http/core/Protocol.hpp"
#include "infrastructure/server/application_protocol/http/router/Router.hpp"
#include "infrastructure/storage/file_system/DirectoryExplorer.hpp"
#include "infrastructure/storage/file_system/Storage.hpp"

namespace webserv {
namespace appProtocol {
class IProtocol;
} // namespace appProtocol
} // namespace webserv

class ServerConfig;

namespace http {

class ProtocolFactory : public webserv::appProtocol::IProtocolFactory
{
  public:
	ProtocolFactory(ServerConfig const &config);
	~ProtocolFactory(void);

	webserv::appProtocol::IProtocol *create();

  private:
	ProtocolFactory(ProtocolFactory const &);
	ProtocolFactory &operator=(ProtocolFactory const &);

	fileSystem::Storage			  _storage;
	fileSystem::DirectoryExplorer _directory_explorer;
	Cgi							  _cgi;

	app::useCase::ServeStaticResource	 _serveStaticResourceUseCase;
	app::useCase::DeleteStaticResource	 _deleteStaticResourceUseCase;
	app::useCase::ExecuteDynamicResource _executeDynamicResourceUseCase;

	ServeStaticResourceController	 _serveStaticResourceController;
	DeleteStaticResourceController	 _deleteStaticResourceController;
	ExecuteDynamicResourceController _executeDynamicResourceController;

	request::Parser	 _requestParser;
	cgi::Parser		 _cgiParser;
	Router			 _router;
	response::Sender _sender;
	Protocol		 _protocol;
};

} // namespace http

#endif // HTTPPROTOCOLFACTORY_HPP
