#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <csignal>
#include <cstdlib>
#include <vector>

#include "server/Server.hpp"
#include "server/utils/Logger.hpp"
#include "infrastructure/config/Config.hpp"
#include "infrastructure/config/ServerConfig.hpp"

void fileCheck(const int argc, const char *argv)
{
	if (argc != 2)
		throw ConfigException("No configuration file passed.");

	const std::string filename = argv;
	if (filename.substr(filename.find_last_of('.') + 1) != "conf")
		throw ConfigException("Configuration file must have a `.conf` extension.");

	const std::ifstream file(argv);
	if (file.fail())
		throw ConfigException("File could not be opened.");
}

// /** main test http module */
// int main(int argc, char **argv)
// {
// 	try
// 	{
// 		fileCheck(argc, argv[1]);
// 		Config					  conf(argv[1]);
// 		std::vector<ServerConfig> server_configs = conf.getServerConfigs();
//
// 		std::vector<ServerConfig>::iterator ite = server_configs.end();
// 		for (std::vector<ServerConfig>::iterator it = server_configs.begin(); it != ite; ++it)
// 		{
// 			ServerConfig		server_config = *it;
// 			fileSystem::Storage storage;
//
// 			fileSystem::DirectoryExplorer	  directory_explorer;
// 			app::useCase::ServeStaticResource serveStaticResource_use_case(
// 				server_config, storage, directory_explorer
// 			);
// 			http::ServeStaticResourceController serveStaticResource_controller(
// 				serveStaticResource_use_case
// 			);
// 			app::useCase::DeleteStaticResource deleteStaticResource_use_case(
// 				server_config, storage
// 			);
// 			http::DeleteStaticResourceController deleteStaticResource_controller(
// 				deleteStaticResource_use_case
// 			);
// 			Cgi									 cgi;
// 			app::useCase::ExecuteDynamicResource executeDynamicResource_use_case(
// 				server_config, cgi
// 			);
// 			http::ExecuteDynamicResourceController executeDynamicResource_controller(
// 				executeDynamicResource_use_case, server_config
// 			);
//
// 			http::request::Parser requestParser(server_config, server_config);
// 			cgi::Parser			  cgiParser(server_config);
// 			http::Router		  router(
// 				server_config, serveStaticResource_controller, deleteStaticResource_controller
// 			);
// 			http::response::Sender sender(server_config);
//
// 			http::Handler	   handler(requestParser, cgiParser, router, sender, server_config);
// 			ITransfertHandler &tranfer = handler;
//
// 			std::string const		requete_test("GET /a/ HTTP/1.0\r\n\r\n");
// 			std::vector<char> const input_buf(requete_test.begin(), requete_test.end());
//
// 			std::string const cgi_response_test(
// 				"Content-Type: text/html\r\n"
// 				"Set-Cookie: cart=110045_77895_53420; SameSite=Strict\r\n"
// 				"Set-Cookie: cart=67; SameSite=Strict\r\n"
// 				"Content-Length: 4\r\n"
// 				"\r\ncaca"
// 			);
// 			std::vector<char> const cgi_input_buf(
// 				cgi_response_test.begin(), cgi_response_test.end()
// 			);
// 			tranfer.prepareContext(0);
//
// 			ITransfertHandler::ProcessingStatus processingStatus;
//
// 			// processingStatus =
// 			// 	tranfer.pushRequest(0, input_buf, ITransfertHandler::RequestStatus::normal);
// 			processingStatus =
// 				tranfer.pushStream(0, cgi_input_buf, ITransfertHandler::StreamStatus::normal);
//
// 			if (processingStatus == ITransfertHandler::complete)
// 			{
// 				while (!tranfer.isResponseComplete(0))
// 				{
// 					std::vector<char> const &output_buf = tranfer.pull(0);
//
// 					std::string const result(output_buf.begin(), output_buf.end());
// 					std::cout << result;
// 				}
// 			}
// 			std::cout << "finish!" << std::endl;
// 		}
// 	}
// 	catch (ConfigException const &e)
// 	{
// 		std::cerr << e.what() << std::endl;
// 		return 1;
// 	}
//
// 	std::cout << "No trouble" << std::endl;
//
// 	return 0;
// }


volatile sig_atomic_t g_running = 1;

static void sigHandler(const int signum) {
  LOG("signal " << signum << " received");
  g_running = 0;
}

static void initSignals() {
  std::signal(SIGINT, sigHandler);
  std::signal(SIGTERM, sigHandler);
  std::signal(SIGPIPE, SIG_IGN);
}

int main(const int argc, char** argv) {
  // std::vector<config::ServerConfig> configs;
  //
  // configs.push_back(config::ServerConfig("localhost", 3000));
  // configs.push_back(config::ServerConfig("0.0.0.0", 8000,
  //                                        config::ServerConfig::TRANSPORT_TCP,
  //                                        config::ServerConfig::APP_TEST));
  // configs.push_back(config::ServerConfig("localhost", 3000));
  // configs.push_back(config::ServerConfig("localhost", 3000));
  try {
  	fileCheck(argc, argv[1]);
  initSignals();
  	const Config					  conf(argv[1]);
  	const std::vector<ServerConfig>& configs = conf.getServerConfigs();

    webserv::Server server(configs);
    server.run();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
