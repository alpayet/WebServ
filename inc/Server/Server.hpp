#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <vector>
# include <map>

# include "../Config/Parser.hpp"


struct Location
{
	std::string					path;
	std::string					root;
	std::vector<std::string>	index;
	std::string					cgi; // maybe vector
	// std::string					methods;
	bool						met_get;
	bool						met_post;
	bool						met_del;
	bool						autoindex;
	int							ret;
};

class Server
{
	public:
		/** CTOR */
		// TODO: constructors / destructor

		/** GETTERS */
		int	getPort() { return m_port; };
		std::string	getInterface() { return m_interface; };
		std::map<int, std::string>	getErrPages() { return m_error_pages; };
		std::vector<Location>	getLocations() { return m_locations; };
		int	getClientMaxBody() { return m_max_body; };
		std::string	getRoot() { return m_root; };
		std::string	getIndex() { return m_index; };

		/** SETTERS */
		void	setPort(int port) { m_port = port; };
		void	setInterface(std::string& interface) { m_interface = interface ; };
		void	addErrPage(int err_nb, std::string& err_path) { m_error_pages[err_nb] = err_path; };
		void	addLocation(Location location) { m_locations.push_back(location); };
		void	setClientMaxBody(long max_body) { m_max_body = max_body; };
		void	setRoot(std::string& root) { m_root = root ; };
		void	setIndex(std::string& index) { m_index = index ; };

		void	setup();

	private:
		int							m_port;
		std::string					m_interface;
		std::map<int, std::string>	m_error_pages;
		std::vector<Location>		m_locations;
		long						m_max_body;
		std::string					m_root;
		std::string					m_index;
};

std::ostream& operator<<(std::ostream& os, const Location& l);
std::ostream& operator<<(std::ostream& os, const Server& s);

#endif
