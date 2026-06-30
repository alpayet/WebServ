#include <fstream>
#include <iostream>
#include <string>

#include "config/Config.hpp"
#include "config/Parser.hpp"
#include "config/Semantic.hpp"
#include "config/Tokenizer.hpp"

#include "application/use_cases/delete_static_resource/DeleteStaticResource.hpp"
#include "application/use_cases/serve_static_resource/ServeStaticResource.hpp"
#include "infrastructure/ITransfertHandler.hpp"
#include "infrastructure/http/Handler.hpp"
#include "infrastructure/http/controllers/DeleteStaticResourceController.hpp"
#include "infrastructure/http/controllers/ServeStaticResourceController.hpp"
#include "infrastructure/http/request/Parser.hpp"
#include "infrastructure/http/response/Sender.hpp"
#include "infrastructure/http/router/Router.hpp"
#include "infrastructure/storage/file_system/DirectoryExplorer.hpp"
#include "infrastructure/storage/file_system/Storage.hpp"

#include <sstream>

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

int main(int argc, char **argv)
{
	try
	{
		fileCheck(argc, argv[1]);
		Config				conf(argv[1]);
		std::vector<Server> server_configs = conf.getServers();

		std::vector<Server>::iterator ite = server_configs.end();
		for (std::vector<Server>::iterator it = server_configs.begin(); it != ite; ++it)
		{
			Server						  server_config = *it;
			fileSystem::Storage			  storage;
			fileSystem::DirectoryExplorer directory_explorer;

			app::useCase::ServeStaticResource serveStaticResource_use_case(
				server_config, storage, directory_explorer
			);
			http::ServeStaticResourceController serveStaticResource_controller(
				serveStaticResource_use_case
			);
			app::useCase::DeleteStaticResource deleteStaticResource_use_case(
				server_config, storage
			);
			http::DeleteStaticResourceController deleteStaticResource_controller(
				deleteStaticResource_use_case
			);

			http::request::Parser parser(server_config, server_config);
			http::Router		  router(
				server_config, serveStaticResource_controller, deleteStaticResource_controller
			);
			http::response::Sender sender(server_config);

			http::Handler	   handler(parser, router, sender);
			ITransfertHandler &tranfer = handler;

			std::string const		requete_test("GET /app/index.html HTTP/1.0\r\n\r\n");
			std::vector<char> const input_buf(requete_test.begin(), requete_test.end());
			tranfer.prepareContext(0);

			tranfer.push(0, input_buf);

			while (!tranfer.isResponseComplete(0))
			{
				std::vector<char> const &output_buf = tranfer.pull(0);

				std::string const result(output_buf.begin(), output_buf.end());
				std::cout << result;
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
