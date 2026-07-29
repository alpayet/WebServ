#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "infrastructure/config/Config.hpp"
#include "infrastructure/config/Parser.hpp"
#include "infrastructure/config/Semantic.hpp"
#include "infrastructure/config/Tokenizer.hpp"

#include "application/use_cases/delete_static_resource/DeleteStaticResource.hpp"
#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.hpp"
#include "application/use_cases/serve_static_resource/ServeStaticResource.hpp"
#include "cgi/Cgi.hpp"
#include "cgi/Parser.hpp"
#include "infrastructure/ITransfertHandler.hpp"
#include "infrastructure/http/Handler.hpp"
#include "infrastructure/http/controllers/DeleteStaticResourceController.hpp"
#include "infrastructure/http/controllers/ExecuteDynamicResourceController.hpp"
#include "infrastructure/http/controllers/ServeStaticResourceController.hpp"
#include "infrastructure/http/request/Parser.hpp"
#include "infrastructure/http/response/Sender.hpp"
#include "infrastructure/http/router/Router.hpp"
#include "infrastructure/storage/file_system/DirectoryExplorer.hpp"
#include "infrastructure/storage/file_system/Storage.hpp"

void fileCheck(int argc, char *argv)
{
	if (argc != 2)
	{
		throw ConfigException("No configuration file passed.");
	}

	std::string filename = argv;
	if (filename.substr(filename.find_last_of(".") + 1) != "conf")
	{
		throw ConfigException("Configuration file must have a `.conf` extention.");
	}

	std::ifstream file(argv);
	if (file.fail())
	{
		throw ConfigException("File couldn't be openned.");
	}
}

/** main test http module */
int main(int argc, char **argv)
{
	try
	{
		fileCheck(argc, argv[1]);
		Config					  conf(argv[1]);
		std::vector<ServerConfig> server_configs = conf.getServerConfigs();

		std::vector<ServerConfig>::iterator ite = server_configs.end();
		for (std::vector<ServerConfig>::iterator it = server_configs.begin(); it != ite; ++it)
		{
			ServerConfig		server_config = *it;
			fileSystem::Storage storage;

			fileSystem::DirectoryExplorer	  directory_explorer;
			app::useCase::ServeStaticResource serve_static_resource_use_case(
				server_config, storage, directory_explorer
			);
			http::ServeStaticResourceController serve_static_resource_controller(
				serve_static_resource_use_case
			);
			app::useCase::DeleteStaticResource delete_static_resource_use_case(
				server_config, storage
			);
			http::DeleteStaticResourceController delete_static_resource_controller(
				delete_static_resource_use_case
			);
			Cgi									 cgi;
			app::useCase::ExecuteDynamicResource execute_dynamic_resource_use_case(
				server_config, cgi
			);
			http::ExecuteDynamicResourceController execute_dynamic_resource_controller(
				execute_dynamic_resource_use_case, server_config
			);

			http::request::Parser request_parser(server_config, server_config);
			cgi::Parser			  cgi_parser(server_config);
			http::Router		  router(
				server_config, serve_static_resource_controller, delete_static_resource_controller
			);
			http::response::Sender sender(server_config);

			http::Handler	   handler(request_parser, cgi_parser, router, sender, server_config);
			ITransfertHandler &tranfer = handler;

			std::string const		request_test("GET /a/ HTTP/1.0\r\n\r\n");
			std::vector<char> const input_buf(request_test.begin(), request_test.end());

			std::string const cgi_response_test(
				"Content-Type: text/html\r\n"
				"Set-Cookie: cart=110045_77895_53420; SameSite=Strict\r\n"
				"Set-Cookie: cart=67; SameSite=Strict\r\n"
				"Content-Length: 4\r\n"
				"\r\ncaca"
			);
			std::vector<char> const cgi_input_buf(
				cgi_response_test.begin(), cgi_response_test.end()
			);
			tranfer.prepareContext(0);

			ITransfertHandler::ProcessingStatus processing_status;

			// processing_status =
			// 	tranfer.pushRequest(0, input_buf, ITransfertHandler::RequestStatus::normal);
			processing_status =
				tranfer.pushStream(0, cgi_input_buf, ITransfertHandler::StreamStatus::normal);

			if (processing_status == ITransfertHandler::complete)
			{
				while (!tranfer.isResponseComplete(0))
				{
					std::vector<char> const &output_buf = tranfer.pull(0);

					std::string const result(output_buf.begin(), output_buf.end());
					std::cout << result;
				}
			}
			std::cout << "finish!" << std::endl;
		}
	}
	catch (ConfigException const &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	std::cout << "No trouble" << std::endl;

	return 0;
}

/** main test config file */
// int main(int argc, char** argv)
// {
// 	try
// 	{
// 		fileCheck(argc, argv[1]);
// 		Config	conf(argv[1]);
// 		std::vector<ServerConfig>::const_iterator	ite = conf.getServerConfigs().end();
// 		for (std::vector<ServerConfig>::const_iterator it = conf.getServerConfigs().begin() ; it !=
// ite ; ++it)
// 		{
// 			std::cout << *it << std::endl;
// 		}
// 	}
// 	catch (const ConfigException& e)
// 	{
// 		std::cerr << e.what() << std::endl;
// 		return 1;
// 	}

// 	std::cout << "No trouble" << std::endl;

// 	return 0;
// }
