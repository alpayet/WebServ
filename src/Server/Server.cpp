
#include "Server/Server.hpp"
#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <map>

#include "Config/Semantic.hpp"

Server::Server()
{
	
}

Server::~Server()
{

}


std::ostream& operator<<(std::ostream& os, const Location& l)
{
	os << "\t***LOCATION***" << std::endl;
	os << "\tPath: " 		<< l.path << std::endl;
	os << "\tRoot: " 		<< l.root << std::endl;
	std::vector<std::string>::const_iterator	ite = l.index.end();
	for (std::vector<std::string>::const_iterator it = l.index.begin() ; it != ite ; ++it)
		os << "\tIndex: " 		<< *it << std::endl;
	os << "\tCGI: " 		<< l.cgi << std::endl;
	os << "\tMethods: " 	<< std::endl;
	os << std::boolalpha  << "\t\tGET= "<< l.met_get << std::endl;
	os << std::boolalpha << "\t\tPOST= " << l.met_post << std::endl;
	os << std::boolalpha << "\t\tDEL= " << l.met_del << std::endl;
	os << "\tAutoindex: " 	<< l.autoindex << std::endl;
	os << "\tReturn: " 		<< l.ret << std::endl;
	os << "\t**ENDLOCATION**" << std::endl;

	return os;
}

std::ostream& operator<<(std::ostream& os, const Server& s)
{
	os << "***SERVER***" << std::endl;

	os << "\tPort: " 					<< s.getPort() << std::endl;
	os << "\tInterface: " 				<< s.getInterface() << std::endl;
	os << "\tRoot: " 					<< s.getRoot() << std::endl;
	os << "\tIndex: " 					<< s.getIndex() << std::endl;
	os << "\tError pages: " 			<< std::endl;
	std::map<int, std::string> err_pages = s.getErrPages();
	std::map<int, std::string>::const_iterator ite = err_pages.end();
	for (std::map<int, std::string>::const_iterator it = err_pages.begin() ; it != ite ; ++it)
	{
		os << "\t\t" << it->first << " => " << it->second << std::endl;
	}
	os << "\tClient max body size: " 	<< s.getClientMaxBody() << std::endl;
	os << "**ENDSERVER**" << std::endl;

	return os;
}
