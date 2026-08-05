#include "infrastructure/server/utils/Logger.hpp"

#include "infrastructure/server/utils/utils.hpp"

Logger::Logger()
{
	std::cout << "[webserv | " << ft::nowFormat() << "] " << "Logger::Logger()" << std::endl;
}

Logger::Logger(std::string const &s)
{

	std::cout << "[" << ft::nowFormat() << "] " << s << std::endl;
}

Logger::~Logger() {}
