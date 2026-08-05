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
#include "cgi/Exception.hpp"
#include <fcntl.h>
#include <iterator>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

bool hasSheBang(std::string const &filename)
{
	int fd = open(filename.c_str(), O_RDONLY);
	if (fd < 0)
		return false;
	char buf[3];
	int	 bytes = read(fd, buf, 2);
	buf[2] = '\0';
	if (bytes <= 0)
		return false;
	if (std::string(buf) == "#!")
		return true;
	return false;
}

std::map<std::string, std::pair<std::string, std::string> > interpreters = {
	{".py", {"/bin/python3", "python3"}},
	{".sh", {"/bin/bash", "bash"}},
	{".php", {"/bin/php", "php"}}
};

std::pair<std::string, std::string> getInterpreter(std::string const &uri)
{
	std::size_t pos = uri.find_last_of(".");

	std::size_t pos2 = uri.find_last_of("/");
	if (pos == std::string::npos || pos2 + 1 == pos)
	{
		throw("banana");
	}

	std::string ext = uri.substr(pos, uri.size() - pos);
	return interpreters[ext];
}

void createEnv(
	std::map<std::string, std::string> const &metaVariables,
	std::vector<std::string>				 &tmpEnv,
	std::vector<char *>						 &envp
)
{
	{
		std::map<std::string, std::string>::const_iterator ite = metaVariables.end();
		std::map<std::string, std::string>::const_iterator it = metaVariables.begin();
		for (; it != ite; ++it)
		{
			tmpEnv.push_back(it->first + "=" + it->second);
		}
	}
	{
		std::vector<std::string>::const_iterator ite = tmpEnv.end();
		std::vector<std::string>::const_iterator it = tmpEnv.begin();
		for (; it != ite; ++it)
		{
			envp.push_back(const_cast<char *>(it->c_str()));
		}
	}
}

// TODO:
// FindStaticResourceUseCase
// ExecuteDynamicResourceUseCase
// content_location = empty if get

void Cgi::execute(
	std::string const						 &resourcePath,
	std::string const						 &bodyPath,
	std::map<std::string, std::string> const &metaVariables
)
{
	// TODO: if post open file at content_location (it's a path)
	std::vector<std::string> tmpEnv;
	std::vector<char *>		 envp; //! need tmpEnv to still exist for it to be use
	createEnv(metaVariables, tmpEnv, envp);

	int fds[2];

	// TODO:
	/**
	 * if executable && hasSheBang
	 * 		execve(direct executable, 0, envp)
	 * else
	 * {
	 * 		interface (pair) = getInterface
	 * 		execve(interface.first, [interface.second, resourcePath], envp)
	 * }
	 */

	if (pipe(fds) < 0)
	{
		throw cgi::Exception(cgi::Exception::PIPE_FAILED);
	}

	pid_t pid = fork();
	if (pid == 0) // child, so cgi
	{
		dup2(fds[0], STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
		execve("/bin/python", [ "python3", "dto.path" ], &envp[0]);
	}
	if (pid == -1)
		throw cgi::Exception(cgi::Exception::FORK_FAILED);
	time_t base_time = time(0);
	int	   status;
	while (waitpid(pid, &status, WNOHANG) != pid)
	{
		if (pid == -1)
			throw("banana");
		time_t curr_time = time(0);
		if (curr_time - base_time > 10) // 10 sec timeout
		{
			kill(pid, SIGKILL);
			waitpid(pid, &status, 0);
			break;
		}
		usleep(14000);
	}
	// if post call function to write body in fsd[1]
	// TODO: ce pas fermer ce fd et le passé a un orchestrateur qui va appelr la methode d'ajoue a
	// epoll du transport
	close(fds[1]);
}

// TODO::? dto will have
/**
 * request_method
 * query_string
 * content_type
 * content_length
 */