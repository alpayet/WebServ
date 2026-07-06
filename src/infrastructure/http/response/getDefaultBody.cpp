/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getDefaultBody.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 01:00:37 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/06 01:42:26 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/response/getDefaultBody.hpp"

namespace http {
char const *getDefaultBody(unsigned short statusCode)
{
	switch (statusCode)
	{
		case 100:
		case 101:
		case 102:
		case 103:
		case 204:
		case 205:
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

		case 201:
			return "<html>\r\n"
				   "<head><title>201 Created</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>201 Created</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 202:
			return "<html>\r\n"
				   "<head><title>202 Accepted</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>202 Accepted</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 203:
			return "<html>\r\n"
				   "<head><title>203 Non-Authoritative Information</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>203 Non-Authoritative Information</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 206:
			return "<html>\r\n"
				   "<head><title>206 Partial Content</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>206 Partial Content</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 207:
			return "<html>\r\n"
				   "<head><title>207 Multi-Status</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>207 Multi-Status</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 208:
			return "<html>\r\n"
				   "<head><title>208 Already Reported</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>208 Already Reported</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 226:
			return "<html>\r\n"
				   "<head><title>226 IM Used</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>226 IM Used</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 300:
			return "<html>\r\n"
				   "<head><title>300 Multiple Choices</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>300 Multiple Choices</h1></center>\r\n"
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

		case 303:
			return "<html>\r\n"
				   "<head><title>303 See Other</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>303 See Other</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 305:
			return "<html>\r\n"
				   "<head><title>305 Use Proxy</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>305 Use Proxy</h1></center>\r\n"
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

		case 308:
			return "<html>\r\n"
				   "<head><title>308 Permanent Redirect</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>308 Permanent Redirect</h1></center>\r\n"
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

		case 401:
			return "<html>\r\n"
				   "<head><title>401 Unauthorized</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>401 Unauthorized</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 402:
			return "<html>\r\n"
				   "<head><title>402 Payment Required</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>402 Payment Required</h1></center>\r\n"
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

		case 406:
			return "<html>\r\n"
				   "<head><title>406 Not Acceptable</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>406 Not Acceptable</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 407:
			return "<html>\r\n"
				   "<head><title>407 Proxy Authentication Required</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>407 Proxy Authentication Required</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 408:
			return "<html>\r\n"
				   "<head><title>408 Request Timeout</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>408 Request Timeout</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 409:
			return "<html>\r\n"
				   "<head><title>409 Conflict</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>409 Conflict</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 410:
			return "<html>\r\n"
				   "<head><title>410 Gone</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>410 Gone</h1></center>\r\n"
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

		case 412:
			return "<html>\r\n"
				   "<head><title>412 Precondition Failed</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>412 Precondition Failed</h1></center>\r\n"
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

		case 415:
			return "<html>\r\n"
				   "<head><title>415 Unsupported Media Type</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>415 Unsupported Media Type</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 416:
			return "<html>\r\n"
				   "<head><title>416 Range Not Satisfiable</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>416 Range Not Satisfiable</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 417:
			return "<html>\r\n"
				   "<head><title>417 Expectation Failed</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>417 Expectation Failed</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 421:
			return "<html>\r\n"
				   "<head><title>421 Misdirected Request</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>421 Misdirected Request</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 422:
			return "<html>\r\n"
				   "<head><title>422 Unprocessable Content</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>422 Unprocessable Content</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 423:
			return "<html>\r\n"
				   "<head><title>423 Locked</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>423 Locked</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 424:
			return "<html>\r\n"
				   "<head><title>424 Failed Dependency</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>424 Failed Dependency</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 425:
			return "<html>\r\n"
				   "<head><title>425 Too Early</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>425 Too Early</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 426:
			return "<html>\r\n"
				   "<head><title>426 Upgrade Required</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>426 Upgrade Required</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 428:
			return "<html>\r\n"
				   "<head><title>428 Precondition Required</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>428 Precondition Required</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 429:
			return "<html>\r\n"
				   "<head><title>429 Too Many Requests</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>429 Too Many Requests</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 431:
			return "<html>\r\n"
				   "<head><title>431 Request Header Fields Too Large</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>431 Request Header Fields Too Large</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 451:
			return "<html>\r\n"
				   "<head><title>451 Unavailable For Legal Reasons</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>451 Unavailable For Legal Reasons</h1></center>\r\n"
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

		case 503:
			return "<html>\r\n"
				   "<head><title>503 Service Unavailable</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>503 Service Unavailable</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 504:
			return "<html>\r\n"
				   "<head><title>504 Gateway Timeout</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>504 Gateway Timeout</h1></center>\r\n"
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

		case 506:
			return "<html>\r\n"
				   "<head><title>506 Variant Also Negotiates</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>506 Variant Also Negotiates</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 507:
			return "<html>\r\n"
				   "<head><title>507 Insufficient Storage</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>507 Insufficient Storage</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 508:
			return "<html>\r\n"
				   "<head><title>508 Loop Detected</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>508 Loop Detected</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 510:
			return "<html>\r\n"
				   "<head><title>510 Not Extended</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>510 Not Extended</h1></center>\r\n"
				   "<hr><center>webserv/1.0</center>\r\n"
				   "</body>\r\n"
				   "</html>\r\n";

		case 511:
			return "<html>\r\n"
				   "<head><title>511 Network Authentication Required</title></head>\r\n"
				   "<body>\r\n"
				   "<center><h1>511 Network Authentication Required</h1></center>\r\n"
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