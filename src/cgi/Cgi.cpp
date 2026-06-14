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

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// cgi for python
void Cgi::execute(
	const std::string			&storage_location,
	const std::string			&content_location,
	ExecuteDynamicResourceInput &dto
)
{
	// TODO: if post open file at content_location (it's a path)
	char *envp[] = {
		("REQUEST_METHOD=" + "dto. ").c_str(),
		("QUERY_STRING="),
		("CONTENT_TYPE="),
		("CONTENT_LENGTH="),
		NULL
	};
	
	int fds[2];

	if (pipe(fds) < 0)
	{
		throw ("banana");
	}

	pid_t pid = fork();
	if (pid == 0) // child, so cgi
	{
		dup2(fds[0], STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
		execve("/bin/python", ["python3", "dto.path"], envp);
	}
	if (pid == -1)
		throw ("banana");
	time_t	base_time = time(0);
	int status;
	while (waitpid(pid, &status, WNOHANG) != pid)
	{
		if (pid == -1)
			throw ("banana");
		time_t curr_time = time (0);
		if (curr_time - base_time > 10) // 10 sec timeout
		{
			kill (pid, SIGKILL);
			waitpid(pid, &status, 0);
			break ;
		}
		usleep(14000);
	}
	// if post call function to write body in fsd[1]
	// TODO: not close and return that fd
	close(fds[1]);
}

//? dto will have
/**
 * request_method
 * query_string
 * content_type
 * content_length
 */