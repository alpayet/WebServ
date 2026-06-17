#ifndef CGI_HPP
#define CGI_HPP

#include "application/ports/IDynamicResourceExecutor.hpp"

class Cgi : public app::IDynamicResourceExecutor
{
  public:
	virtual void execute(
		std::string const						 &resourcePath,
		std::string const						 &bodyPath,
		std::map<std::string, std::string> const &metaVariables
	);

  private:
};

#endif
