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
#include "infrastructure/server/utils/Logger.hpp"

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

void createEnv(std::map<std::string, std::string> const& meta_variables, std::vector<std::string>& tmp_env,
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

void childRoutine(const std::string& rootPath, const std::string& uri, const std::string& body_path, int pipe_fds[2],
                  const std::vector<char*>& envp)
{
    std::pair<std::string, std::string> interpreter;
    const bool hasInterpreter = getInterpreter(uri, interpreter);

    std::size_t slash = uri.find_last_of('/');
    const std::string script = uri.substr(slash + 1);

    const char* in = body_path.empty() ? "/dev/null" : body_path.c_str();
    int in_fd = ::open(in, O_RDONLY);
    if (in_fd < 0 || ::dup2(pipe_fds[1], STDOUT_FILENO) < 0 || ::dup2(in_fd, STDIN_FILENO) < 0 ||
        ::chdir(rootPath.c_str()) < 0)
        ::_exit(1);


    // close read buf not using and close write buf now dup in new_write_buf
    ::close(in_fd);
    ::close(pipe_fds[0]);
    ::close(pipe_fds[1]);

    if (hasInterpreter)
    {
        char* argv[3] = {const_cast<char*>(interpreter.second.c_str()), const_cast<char*>(script.c_str()), NULL};
        ::execve(interpreter.first.c_str(), argv, &envp[0]);
    }
    else
    {
        std::cerr << "does not has interpreter" << std::endl;

        std::string exec_path = "./" + script;
        char* argv[2] = {const_cast<char*>(uri.c_str()), NULL};
        ::execve(exec_path.c_str(), argv, &envp[0]);
    }
    std::cerr << "execve() failed in child" << std::endl;
    ::_exit(1);
}

app::StreamInfo Cgi::execute(const std::string& rootPath, const std::string& resourcePath, const std::string& bodyPath,
                             const std::map<std::string, std::string>& meta_variables)
{
    app::StreamInfo infos = {-1, -1};
    std::vector<std::string> tmp_env;
    std::vector<char*> envp;
    int pipe_fds[2];

    createEnv(meta_variables, tmp_env, envp);

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
        childRoutine(rootPath, resourcePath, bodyPath, pipe_fds, envp);

    ::close(pipe_fds[1]);

    if (::fcntl(pipe_fds[0], F_SETFL, O_NONBLOCK) == -1)
    {
        ::close(pipe_fds[0]);
        ::kill(infos.pid, SIGKILL);
        ::waitpid(infos.pid, NULL, 0);
        throw cgi::Exception(cgi::Exception::SET_NON_BLOCK_FAILED);
    }

    infos.fd = pipe_fds[0];

    DEBUG("CGI fd: " << infos.fd);

    return infos;
}

// // TODO::? dto will have
// /**
//  * request_method
//  * query_string
//  * content_type
//  * content_length
//  */
