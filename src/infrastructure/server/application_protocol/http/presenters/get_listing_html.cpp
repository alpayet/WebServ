/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_listing_html.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 01:22:23 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:14:19 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/presenters/get_listing_html.hpp"

namespace webserv {
namespace http {
std::string get_listing_html(std::string const &uri, std::vector<app::CollectionEntry> const &files)
{
	std::string listing;

	listing += "<!DOCTYPE html>\n";
	listing += "<html>\n";
	listing += "<head>\n";
	listing += "<title>Directory listing</title>\n";
	listing += "<style type=\"text/css\">\n";
	listing += "td { padding: 0 15px; }\n";
	listing += "</style>\n";
	listing += "</head>\n";
	listing += "<h1>Index of " + uri + "</h1>\n";
	listing += "<table>\n";
	listing += "\t<tr>\n";
	listing += "\t\t<th>Name</th>\n";
	listing += "\t\t<th>Last Modified</th>\n";
	listing += "\t\t<th>Size</th>\n";
	listing += "\t</tr>\n";

	std::vector<app::CollectionEntry>::const_iterator ite = files.end();
	std::vector<app::CollectionEntry>::const_iterator it = files.begin();
	for (; it != ite; ++it)
	{
		if (!it->name.empty())
		{
			listing += "\t<tr>\n";
			listing += "\t\t<td><a href=\"" + it->id + "\">" + it->name + "</a></td>\n";
			listing += "\t\t<td>" + it->lastMod + "</td>\n";
			listing += "\t\t<td>" + it->size + "</td>\n";
			listing += "\t</tr>\n";
		}
	}

	listing += "</table>\n";
	listing += "</body>\n";
	listing += "</html>\n";

	return listing;
}
} // namespace http
}
