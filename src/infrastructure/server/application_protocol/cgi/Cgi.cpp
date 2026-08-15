#include "infrastructure/server/application_protocol/cgi/Cgi.hpp"

#include <csignal>
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include "infrastructure/server/application_protocol/cgi/Exception.hpp"

namespace webserv {
	bool getInterpreter(const std::string& uri, std::pair<std::string, std::string>& out)
	{
		std::map<std::string, std::pair<std::string, std::string> > interpreters;

		interpreters[".sh"] = std::make_pair("/bin/bash", "bash");
		interpreters[".py"] = std::make_pair("/usr/bin/python3", "python3");
		interpreters[".php"] = std::make_pair("/usr/bin/php", "php");
		// interpreters[".py"] = std::make_pair("/null/test/python3", "python3");
		// interpreters[".py"] = std::make_pair("/bin/python3", "python3");
		// interpreters[".php"] = std::make_pair("/bin/php", "php");

		std::size_t dot = uri.find_last_of('.');
		std::size_t slash = uri.find_last_of('/');

		if (dot == std::string::npos || dot < slash)
			return false;

		const std::string ext = uri.substr(dot);

		std::map<std::string, std::pair<std::string, std::string> >::const_iterator it = interpreters.find(ext);
		if (it == interpreters.end())
			return false;

		out = it->second;
		return true;
	}

	void createEnv(const std::map<std::string, std::string>& meta_variables, std::vector<std::string>& tmp_env,
	               std::vector<char*>& envp)
	{
		{
			const std::map<std::string, std::string>::const_iterator ite = meta_variables.end();
			std::map<std::string, std::string>::const_iterator it = meta_variables.begin();
			for (; it != ite; ++it) tmp_env.push_back(it->first + "=" + it->second);
		}
		{
			const std::vector<std::string>::const_iterator ite = tmp_env.end();
			std::vector<std::string>::const_iterator it = tmp_env.begin();
			for (; it != ite; ++it) envp.push_back(const_cast<char*>(it->c_str()));

			envp.push_back(NULL);
		}
	}

	void childRoutine(const std::string& root_path, const std::string& body_path, int pipe_fds[2],
	                  const char* exec_path, char* const* argv, char* const* envp)
	{
		const char* in = body_path.empty() ? "/dev/null" : body_path.c_str();
		int in_fd = ::open(in, O_RDONLY);
		if (in_fd < 0 || ::dup2(pipe_fds[1], STDOUT_FILENO) < 0 || ::dup2(in_fd, STDIN_FILENO) < 0 ||
		    ::chdir(root_path.c_str()) < 0)
			::_exit(EXIT_FAILURE);

		::close(in_fd);
		::close(pipe_fds[0]);
		::close(pipe_fds[1]);

		::execve(exec_path, argv, envp);

		::_exit(EXIT_FAILURE);
	}

	app::StreamInfo Cgi::execute(const std::string& root_path, const std::string& resource_path,
	                             const std::string& body_path, const std::map<std::string, std::string>& meta_variables)
	{
		app::StreamInfo infos = {-1, -1};
		std::pair<std::string, std::string> interpreter;
		const bool hasInterpreter = getInterpreter(resource_path, interpreter);
		const std::size_t slash = resource_path.find_last_of('/');
		const std::string script = resource_path.substr(slash + 1);
		const std::string exec_path = hasInterpreter ? interpreter.first : ("./" + script);
		std::vector<char*> argv; 
		argv.reserve(3);
		if (hasInterpreter)
		{
			argv.push_back(const_cast<char*>(interpreter.second.c_str()));
			argv.push_back(const_cast<char*>(script.c_str()));
		}
		else
			argv.push_back(const_cast<char*>(resource_path.c_str()));
		argv.push_back(NULL);

		std::vector<std::string> tmp_env;
		std::vector<char*> envp;
		createEnv(meta_variables, tmp_env, envp);

		int pipe_fds[2];
		if (::pipe(pipe_fds) < 0)
			throw cgi::Exception(cgi::Exception::PIPE_FAILED);

		infos.pid = ::fork();
		if (infos.pid == -1)
		{
			::close(pipe_fds[0]);
			::close(pipe_fds[1]);
			throw cgi::Exception(cgi::Exception::FORK_FAILED);
		}
		if (infos.pid == 0)
			childRoutine(root_path, body_path, pipe_fds, exec_path.c_str(), &argv[0], &envp[0]);

		::close(pipe_fds[1]);

		if (::fcntl(pipe_fds[0], F_SETFL, O_NONBLOCK) == -1)
		{
			::close(pipe_fds[0]);
			::kill(infos.pid, SIGKILL);
			::waitpid(infos.pid, NULL, 0);
			throw cgi::Exception(cgi::Exception::SET_NON_BLOCK_FAILED);
		}

		infos.fd = pipe_fds[0];

		return infos;
	}
} // namespace webserv
