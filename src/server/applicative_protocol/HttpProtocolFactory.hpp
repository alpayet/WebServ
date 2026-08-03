#ifndef HTTPPROTOCOLFACTORY_HPP
#define HTTPPROTOCOLFACTORY_HPP

#include "application/use_cases/delete_static_resource/DeleteStaticResource.hpp"
#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.hpp"
#include "application/use_cases/serve_static_resource/ServeStaticResource.hpp"
#include "cgi/Cgi.hpp"
#include "infrastructure/http/Handler.hpp"
#include "infrastructure/http/controllers/DeleteStaticResourceController.hpp"
#include "infrastructure/http/controllers/ExecuteDynamicResourceController.hpp"
#include "infrastructure/http/controllers/ServeStaticResourceController.hpp"
#include "infrastructure/http/router/Router.hpp"
#include "infrastructure/storage/file_system/DirectoryExplorer.hpp"
#include "infrastructure/storage/file_system/Storage.hpp"
#include "server/applicative_protocol/IProtocolFactory.hpp"

class ServerConfig;

namespace webserv {
namespace protocol {

class IProtocol;

class HttpProtocolFactory : public IProtocolFactory {
public:
  explicit HttpProtocolFactory(const ::ServerConfig &config);
  ~HttpProtocolFactory();

  IProtocol *create();

private:
  HttpProtocolFactory(const HttpProtocolFactory &);
  HttpProtocolFactory &operator=(const HttpProtocolFactory &);

  fileSystem::Storage _storage;
  fileSystem::DirectoryExplorer _directory_explorer;
  Cgi _cgi;

  app::useCase::ServeStaticResource _serveStaticResourceUseCase;
  app::useCase::DeleteStaticResource _deleteStaticResourceUseCase;
  app::useCase::ExecuteDynamicResource _executeDynamicResourceUseCase;

  http::ServeStaticResourceController _serveStaticResourceController;
  http::DeleteStaticResourceController _deleteStaticResourceController;
  http::ExecuteDynamicResourceController _executeDynamicResourceController;

  http::request::Parser _requestParser;
  cgi::Parser _cgiParser;
  http::Router _router;
  http::response::Sender _sender;
  http::Handler _handler;
};

} // namespace protocol
} // namespace webserv

#endif // HTTPPROTOCOLFACTORY_HPP
