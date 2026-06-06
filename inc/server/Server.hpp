#ifndef SERVER_HPP
#define SERVER_HPP

#include "infrastructure/http/parsers/IRequestValidationPolicy.hpp"
#include "infrastructure/http/router/IRouteAccessValidator.hpp"
#include "infrastructure/repositories/IResourceLocator.hpp"
#include <map>
#include <string>
#include <vector>

struct Location
{
	std::string				 path;
	std::string				 root;
	std::vector<std::string> index;
	std::vector<std::string> cgi;
	bool					 met_get;
	bool					 met_post;
	bool					 met_del;
	bool					 autoindex;
	int						 ret;

	Location() : met_get(true), met_post(true), met_del(true), autoindex(false), ret(0) {};
};

class Server : public IResourceLocator,
			   public http::IRouteAccessValidator,
			   public http::IRequestValidationPolicy
{
  public:
	/** CTOR */
	Server() : m_port(8080), m_interface("0.0.0.0"), m_max_body(1000000) {};
	~Server() {};

	/** GETTERS */
	uint16_t						  getPort() const { return m_port; };
	const std::string				 &getInterface() const { return m_interface; };
	const std::map<int, std::string> &getErrPages() const { return m_error_pages; };
	const std::vector<Location>		 &getLocations() const { return m_locations; };
	int								  getClientMaxBody() const { return m_max_body; };
	const std::string				 &getRoot() const { return m_root; };
	const std::string				 &getIndex() const { return m_index; };

	/** SETTERS */
	void setPort(int port) { m_port = port; };
	void setInterface(const std::string &interface) { m_interface = interface; };
	void addErrPage(int err_nb, const std::string &err_path) { m_error_pages[err_nb] = err_path; };
	void addLocation(const Location &location) { m_locations.push_back(location); };
	void setClientMaxBody(long max_body) { m_max_body = max_body; };
	void setRoot(const std::string &root) { m_root = root; };
	void setIndex(const std::string &index) { m_index = index; };

	/** GETTERS from parents */
	virtual std::string				 resolvePhysicalPath(std::string const &uri) const;
	virtual std::vector<std::string> getAllowedMethods(std::string const &uri) const;
	virtual std::size_t				 getMaxBodySize(std::string const &uri) const; // void param

  private:
	short					   m_port;
	std::string				   m_interface;
	std::map<int, std::string> m_error_pages;
	std::vector<Location>	   m_locations;
	std::size_t				   m_max_body;
	std::string				   m_root;
	std::string				   m_index;
};

std::ostream &operator<<(std::ostream &os, const Location &l);
std::ostream &operator<<(std::ostream &os, const Server &s);

#endif
