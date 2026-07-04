/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generateDefaultBody.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 23:06:22 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/04 22:33:21 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/exceptions/generateDefaultBody.hpp"

// TODO: a voir pour le nom du serveur a mettre dnas un define ou pas

// TODO: int ou unsigned short pour statusCode
namespace http {
char const *generateDefaultBody(unsigned short statusCode)
{
	switch (statusCode)
	{
		case 204:
		case 304:
			return "";

		case 200:
			return "<html>\r\n"
				   "<head><title>200 OK</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>200 OK</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 301:
			return "<html>\r\n"
				   "<head><title>301 Moved Permanently</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>301 Moved Permanently</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 302:
			return "<html>\r\n"
				   "<head><title>302 Found</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>302 Found</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 307:
			return "<html>\r\n"
				   "<head><title>307 Temporary Redirect</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>307 Temporary Redirect</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 400:
			return "<html>\r\n"
				   "<head><title>400 Bad Request</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>400 Bad Request</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 403:
			return "<html>\r\n"
				   "<head><title>403 Forbidden</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>403 Forbidden</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 404:
			return "<html>\r\n"
				   "<head><title>404 Not Found</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>404 Not Found</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 405:
			return "<html>\r\n"
				   "<head><title>405 Method Not Allowed</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>405 Method Not Allowed</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 411:
			return "<html>\r\n"
				   "<head><title>411 Length Required</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>411 Length Required</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 413:
			return "<html>\r\n"
				   "<head><title>413 Content Too Large</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>413 Content Too Large</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 414:
			return "<html>\r\n"
				   "<head><title>414 URI Too Long</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>414 URI Too Long</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 500:
			return "<html>\r\n"
				   "<head><title>500 Internal Server Error</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>500 Internal Server Error</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 501:
			return "<html>\r\n"
				   "<head><title>501 Not Implemented</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>501 Not Implemented</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 502:
			return "<html>\r\n"
				   "<head><title>502 Bad Gateway</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>502 Bad Gateway</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 505:
			return "<html>\r\n"
				   "<head><title>505 HTTP Version Not Supported</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>505 HTTP Version Not Supported</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		default:
			return "<html>\r\n"
				   "<head><title>Unknown Status Code</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>Execution Status Acknowledged</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";
	}
}
} // namespace http
