
#include "Server/Server.hpp"
#include <iostream>

// std::ostream& operator<<(std::ostream& os, const Location& l)
// {
// 	os << "\t***LOCATION***" << std::endl;
// 	os << "\tPath: " 		<< l.path << std::endl;
// 	os << "\tRoot: " 		<< l.root << std::endl;
// 	os << "\tIndex: " 		<< l.index << std::endl;
// 	os << "\tCGI: " 		<< l.cgi << std::endl;
// 	os << "\tMethods: " 	<< l.methods << std::endl;
// 	os << "\tAutoindex: " 	<< l.autoindex << std::endl;
// 	os << "\tReturn: " 		<< l.ret << std::endl;
// 	os << "\t**ENDLOCATION**" << std::endl;

// 	return os;
// }

// std::ostream& operator<<(std::ostream& os, const Server& s)
// {
// 	os << "***SERVER***" << std::endl;

// 	os << "\t***DIRECTIVE***" << std::endl;
// 	os << "\tPort: " 					<< s.getPort() << std::endl;
// 	os << "\tName: " 					<< s.getName() << std::endl;
// 	// TODO: for
// 	std::vector<Directive>::const_iterator d_ite = s_it->directives.end();
// 	for (std::vector<Directive>::const_iterator d_it = s_it->directives.begin() ; d_it != d_ite ; *d_it++)
// 	{
// 		os << "\tError pages: " 			<< s << std::endl;
// 	}
// 	// endfor
// 	os << "\tClient max body size: " 	<< s.getClientMaxBody() << std::endl;
// 	os << "\t**ENDDIRECTIVE**" << std::endl;

// 	os << "**ENDSERVER**" << std::endl;

// 	return os;
// }
