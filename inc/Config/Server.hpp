#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <vector>
# include <map>

# include "Parser.hpp"


struct Location
{
	std::string	path;
	std::string	root;
	std::string	index;
	std::string	cgi; // maybe vector
	std::string	methods;
	std::string	autoindex;
	int			ret;
};

class Server
{
	public:
		/** CTOR */
		// TODO: constructors / destructor

		/** GETTERS */
		int	getPort() { return m_port; };
		std::string	getName() { return m_name; };
		std::map<int, std::string>	getErrPages() { return m_error_pages; };
		std::vector<Location>	getLocations() { return m_locations; };
		int	getClientMaxBody() { return m_max_body; };

		/** SETTERS */
		void	setPort(int port) { m_port = port; };
		void	setName(std::string& name) { m_name = name ; };
		void	addErrPages(int err_nb, std::string& err_path) { m_error_pages[err_nb] = err_path; };
		void	addLocations(Location location) { m_locations.push_back(location); };
		void	setClientMaxBody(int max_body) { m_max_body = max_body; };

	private:
		int							m_port;
		std::string					m_name;
		std::map<int, std::string>	m_error_pages;
		std::vector<Location>		m_locations;
		int							m_max_body;
};

#endif
