/**
 * cgi logic
 * server gets request from client
 * selects script
 * client request become cgi request
 * executes script
 * cgi response become client response
 */

/**
 * cgi GET
 */

/**
 * cgi POST
 */

/**
 * cgi arg in uri?
 */

/**
 * cgi type
 * identify script language
 */

#include "cgi/Cgi.hpp"
#include <string>

// TODO:
// FindStaticResourceUseCase
// ExecuteDynamicResourceUseCase
// content_location = empty if get
void getInterpreter(const std::string &filename)
{
	std::size_t pos = filename.find_last_of(".");

	if (pos == std::string::npos)
	{
		throw("banana");
		// TODO : if she-bang, no throw
	}
}

void Cgi::execute(
	const std::string			&storage_location,
	const std::string			&content_location,
	ExecuteDynamicResourceInput &dto
)
{
	// TODO: make pointer array (env) with dto infos to pass to execve
	int *p[1024];

	// TODO: if post open file at content_location (it's a path)
}

//? dto will have
/**
 * request_method
 * query_string
 * content_type
 * content_length
 */