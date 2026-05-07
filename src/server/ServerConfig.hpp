#ifndef SERVERCONFIG_HPP
#define SERVERCONFIG_HPP

#include <string>
#include <vector>

struct Location {
  std::string path;
  std::string root;
  std::string index;
  std::string cgi;  // maybe vector
  std::string methods;
  std::string autoindex;
  int ret;
};

class ServerConfig {
 public:
  ServerConfig();
  ~ServerConfig();

  std::string getHost() const;
  int getPort() const;

 private:
  std::string m_host;
  int m_port;
  std::vector<std::string> m_server_names;
  std::vector<Location> m_locations;
};

#endif  // SERVERCONFIG_HPP
