#include "infrastructure/config/Config.hpp"
#include "infrastructure/config/Parser.hpp"
#include "infrastructure/config/Semantic.hpp"
#include "infrastructure/config/Tokenizer.hpp"
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

namespace webserv {
Config::Config(char const *filename)
{
	std::ifstream file(filename);
	if (file.fail())
	{
		throw ConfigException("File couldn't be openned.");
	}

	std::ostringstream buf;
	buf << file.rdbuf();
	std::string tmp_file_str = buf.str();

	std::string file_str;
	for (std::size_t i = 0; i < tmp_file_str.size();)
	{
		if (tmp_file_str[i] == '#')
		{
			std::size_t nl = tmp_file_str.find('\n', i);
			i = (nl == std::string::npos) ? tmp_file_str.size() : nl;
		}
		else
			file_str += tmp_file_str[i++];
	}

	Tokenizer tok;
	tok.tokenize(file_str);
	if (tok.getTokens().empty())
	{
		throw ConfigException("File is empty.");
	}

	Parser	 prs(tok.getTokens());
	p_Config conf;
	prs.parse(conf);

	checkDupHostname(conf);
	for (size_t i = 0; i < conf.servers.size(); ++i)
	{
		checkDupLoc(conf.servers[i]);
	}

	std::vector<p_ServerConfig>::const_iterator ite = conf.servers.end();
	for (std::vector<p_ServerConfig>::const_iterator it = conf.servers.begin(); it != ite; ++it)
	{
		ServerConfig serv;
		initServerConfig(serv, *it);
		initLocation(serv, *it);
		this->m_servers.push_back(serv);
	}
}
} // namespace webserv
