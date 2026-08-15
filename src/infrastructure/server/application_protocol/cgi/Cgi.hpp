#ifndef CGI_HPP
#define CGI_HPP

#include "application/ports/IDynamicResourceExecutor.hpp"

namespace webserv {
class Cgi : public app::IDynamicResourceExecutor
{
  public:
	app::StreamInfo execute(
		std::string const						 &rootPath,
		std::string const						 &resourcePath,
		std::string const						 &bodyPath,
		std::map<std::string, std::string> const &metaVariables
	);
};
} // namespace webserv

#endif
