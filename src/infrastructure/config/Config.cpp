#include <fstream>
#include <sstream>
#include <iostream>
#include "config/Config.hpp"
#include "config/Tokenizer.hpp"
#include "config/Parser.hpp"
#include "config/Semantic.hpp"
#include <vector>
#include <iterator>

Config::Config(char* filename)
{
	std::ifstream	file(filename);
	if (file.fail())
	{
		throw ConfigException ("File couldn't be openned.");
	}

	std::ostringstream buf;
	buf << file.rdbuf();
	std::string file_str = buf.str();

	Tokenizer tok;
	tok.tokenize(file_str);
	if (tok.getTokens().empty())
	{
		throw ConfigException ("File is empty.");
	}

	Parser prs(tok.getTokens());
	p_Config conf;
	prs.parse(conf);

	checkDupHostname(conf);
	for (size_t i = 0 ; i < conf.servers.size() ; ++i)
	{
		checkDupLoc(conf.servers[i]);
	}

	std::vector<p_ServerConfig>::const_iterator ite = conf.servers.end();
	for (std::vector<p_ServerConfig>::const_iterator it = conf.servers.begin() ; it != ite ; ++it)
	{
		ServerConfig serv;
		initServerConfig(serv, *it);
		initLocation(serv, *it);
		this->m_servers.push_back(serv);
	}
	
}
