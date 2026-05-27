#include <iostream>
#include <string>
#include <fstream>

#include "Config/Tokenizer.hpp"
#include "Config/Parser.hpp"
#include "Config/Semantic.hpp"
#include "Config/Config.hpp"


#include <sstream>

void	fileCheck(int argc, char* argv)
{
	if (argc != 2)
	{
		throw ConfigException ("No configuration file passed.");
	}

	std::string filename = argv;
	if (filename.substr(filename.find_last_of(".") + 1) != "conf")
	{
		throw ConfigException ("Configuration file must have a `.conf` extention.");
	}

	std::ifstream	file(argv);
	if (file.fail())
	{
		throw ConfigException ("File couldn't be openned.");
	}
}

int main(int argc, char** argv)
{
	try
	{
		fileCheck(argc, argv[1]);
		Config	conf(argv[1]);
		std::vector<Server>::const_iterator	ite = conf.getServers().end();
		for (std::vector<Server>::const_iterator it = conf.getServers().begin() ; it != ite ; ++it)
		{
			std::cout << *it << std::endl;
		}
	}
	catch (const ConfigException& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	std::cout << "No trouble" << std::endl;

	return 0;
}
