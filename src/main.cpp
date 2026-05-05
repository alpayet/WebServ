#include <iostream>
#include <string>
#include <fstream>

#include "Config/Tokenizer.hpp"
#include "Config/Parser.hpp"

bool	basicCheck(int argc, char* argv)
{
	if (argc != 2)
	{
		std::cerr << "Error.\nNo configuration file passed." << std::endl;
		return false;
	}

	std::string filename = argv;
	if (filename.substr(filename.find_last_of(".") + 1) != "conf")
	{
		std::cerr << "Error.\nConfiguration file must have a `.conf` extention." << std::endl;
		return false;
	}

	std::ifstream	file(argv);
	if (file.fail())
	{
		std::cerr << "Error.\nFile couldn't be openned." << std::endl;
		return false;
	}
	return true;
}
#include <sstream>

int main(int argc, char** argv)
{
	if (basicCheck(argc, argv[1]) == false)
		return 1;

	// std::string filename = argv[1];
	std::ifstream	file(argv[1]);
	if (file.fail())
	{
		std::cerr << "Error.\nFile couldn't be openned." << std::endl;
		return 1;
	}

	std::ostringstream buf;
	buf << file.rdbuf();
	std::string file_str = buf.str();

	Tokenizer tok;
	tok.tokenize(file_str);

	// if (debug)
	// std::cout << tok << std::endl;

	Parser prs(tok.getTokens());
	Config conf;
	if (!prs.parse(conf))
	{
		return 1;
	}
	std::cout << conf << std::endl;

	return 0;
}
