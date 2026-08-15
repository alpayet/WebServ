#ifndef CGI_HPP
#define CGI_HPP

#include "application/ports/IDynamicResourceExecutor.hpp"

class Cgi : public app::IDynamicResourceExecutor
{
public:
	app::StreamInfo execute(const std::string& root_path, const std::string& resource_path,
	                        const std::string& body_path, const std::map<std::string, std::string>& meta_variables);
};

#endif
