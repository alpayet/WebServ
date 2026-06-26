#ifndef SERVER_HPP
#define SERVER_HPP

#include "application/ports/IResourceLocator.hpp"
#include "infrastructure/http/IHttpVersionProvider.hpp"
#include "infrastructure/http/controllers/ILimitsProvider.hpp"
#include "infrastructure/http/request/IRequestValidationPolicy.hpp"
#include "infrastructure/http/router/IRouteRegistry.hpp"
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

class Server : public app::IResourceLocator,
			   public http::IRequestValidationPolicy,
			   public http::ILimitsProvider,
			   public http::IRouteRegistry,
			   public http::IHttpVersionProvider
{
  public:
	/** CTOR */
	Server()
		: m_port(8080), m_interface("0.0.0.0"), m_max_body(1000000), m_transport(TRANSPORT_TCP),
		  m_applicative_protocol(APP_HTTP) {};
	~Server() {};

	enum TransportProtocol
	{
		TRANSPORT_TCP,
		TRANSPORT_UDP
	};

	enum ApplicativeProtocol
	{
		APP_HTTP,
		APP_TEST
	};

	/** GETTERS */
	unsigned short					  getPort() const { return m_port; };
	std::string const				 &getInterface() const { return m_interface; };
	std::map<int, std::string> const &getErrPages() const { return m_error_pages; };
	std::vector<Location> const		 &getLocations() const { return m_locations; };
	int								  getClientMaxBody() const { return m_max_body; };
	std::string const				 &getRoot() const { return m_root; };
	std::vector<std::string> const	 &getIndex() const { return m_index; };

	/** SETTERS */
	void setPort(int port) { m_port = port; };
	void setInterface(std::string const &interface) { m_interface = interface; };
	void addErrPage(int err_nb, std::string const &err_path) { m_error_pages[err_nb] = err_path; };
	void addLocation(Location const &location) { m_locations.push_back(location); };
	void setClientMaxBody(long max_body) { m_max_body = max_body; };
	void setRoot(std::string const &root) { m_root = root; };
	void addIndex(std::string const &index) { m_index.push_back(index); };

	/** GETTERS from parents */
	std::string resolvePhysicalPath(
		std::string const &uri, std::string const &matchedRoute, std::string const &rootPath
	) const;
	Location				 findLocationFromUri(std::string const &uri) const;
	virtual std::string		 getHttpVersion(void) const;
	virtual std::size_t		 getMaxRequestLineSize(void) const;
	virtual std::size_t		 getMaxHeaderLineSize(void) const;
	virtual std::size_t		 getMaxHeaderCount(void) const;
	virtual std::size_t		 getMaxBodySize(void) const; // void param
	virtual std::size_t		 getMaxBodySize(std::string const &uri) const;
	std::vector<std::string> getAllowedMethods(Location const &loc) const;
	TransportProtocol		 getTransportProtocol(void) const;
	ApplicativeProtocol		 getApplicativeProtocol(void) const;

	virtual app::SystemResourceInfos locate(
		std::string const &id, std::string const &matchedRoute, std::string const &rootPath
	) const;
	virtual app::SystemResourceInfos locateDefaultIndex(
		std::vector<std::string> const &indexesId,
		std::string const			   &matchedRoute,
		std::string const			   &rootPath
	) const;

	virtual http::RoutePolicy match(std::string const &uri) const;

  private:
	unsigned short			   m_port;
	std::string				   m_interface;
	std::map<int, std::string> m_error_pages;
	std::vector<Location>	   m_locations;
	std::size_t				   m_max_body;
	std::string				   m_root;
	std::vector<std::string>   m_index;
	TransportProtocol		   m_transport;
	ApplicativeProtocol		   m_applicative_protocol;
};

std::ostream &operator<<(std::ostream &os, Location const &l);
std::ostream &operator<<(std::ostream &os, Server const &s);

#endif
