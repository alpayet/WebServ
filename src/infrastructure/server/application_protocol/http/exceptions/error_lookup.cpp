/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_lookup.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 04:00:23 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/05 03:35:13 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/exceptions/error_lookup.hpp"

namespace http {
unsigned short to_status_code(Exception::ErrorCode error_code)
{
	switch (error_code)
	{
		case Exception::LINE_BREAK_INVALID:
		case Exception::REQUEST_LINE_MALFORMED:
		case Exception::HEADER_LINE_MALFORMED:
		case Exception::METHOD_INVALID:
		case Exception::TARGET_INVALID:
		case Exception::HEADER_KEY_INVALID:
		case Exception::HEADER_VALUE_INVALID:
		case Exception::CONTENT_LENGTH_INVALID:
			return (400);
		case Exception::MATCH_ROUTE_FAILED:
			return (404);
		case Exception::METHOD_NOT_ALLOWED:
			return (405);
		case Exception::TIMEOUT:
			return (408);
		case Exception::CONTENT_LENGTH_REQUIRED:
			return (411);
		case Exception::BODY_TOO_LARGE:
			return (413);
		case Exception::REQUEST_LINE_TOO_LARGE:
			return (414);
		case Exception::HEADER_LINE_TOO_LARGE:
		case Exception::HEADER_COUNT_TOO_LARGE:
			return (431);
		case Exception::MAX_LOCAL_REDIR_DEPTH_EXCEEDED:
			return (500);
		case Exception::VERSION_INVALID:
			return (505);
		default:
			return (500);
	}
}

unsigned short to_status_code(fileSystem::Exception::ErrorCode error_code)
{
	(void)error_code;
	return (500);
}

unsigned short to_status_code(cgi::Exception::ErrorCode error_code)
{
	switch (error_code)
	{
		case cgi::Exception::PIPE_FAILED:
		case cgi::Exception::FORK_FAILED:
			return (500);
		case cgi::Exception::DOC_RESPONSE_MALFORMED:
		case cgi::Exception::LOCAL_REDIR_RESPONSE_MALFORMED:
		case cgi::Exception::CLIENT_REDIR_RESPONSE_MALFORMED:
		case cgi::Exception::CLIENT_REDIR_DOC_RESPONSE_MALFORMED:
		case cgi::Exception::STATUS_CODE_INVALID:
		case cgi::Exception::STATUS_REASON_INVALID:
		case cgi::Exception::LOCATION_INVALID:
		case cgi::Exception::LINE_BREAK_INVALID:
		case cgi::Exception::HEADER_LINE_MALFORMED:
		case cgi::Exception::HEADER_KEY_INVALID:
		case cgi::Exception::HEADER_VALUE_INVALID:
		case cgi::Exception::CONTENT_LENGTH_INVALID:
		case cgi::Exception::HEADER_LINE_TOO_LARGE:
		case cgi::Exception::HEADER_COUNT_TOO_LARGE:
		case cgi::Exception::BODY_TOO_LARGE:
		case cgi::Exception::BODY_SIZE_MISMATCH:
		case cgi::Exception::PREMATURE_EOF:
			return (502);
		case cgi::Exception::TIMEOUT:
			return (504);
		default:
			return (500);
	}
}

unsigned short to_status_code(app::Exception::ErrorCode error_code)
{
	switch (error_code)
	{
		case app::Exception::PATH_TRAVERSAL_DETECTED:
			return (400);
		case app::Exception::ACCESS_DENIED:
		case app::Exception::LISTING_DISABLED:
			return (403);
		case app::Exception::NOT_FOUND:
			return (404);
		case app::Exception::DELETE_FAILED:
			return (500);
		default:
			return (500);
	}
}

unsigned short to_status_code(domain::Exception::ErrorCode error_code)
{
	switch (error_code)
	{
		case domain::Exception::PATH_MISSING:
			return (404);
		case domain::Exception::TYPE_UNSUPPORTED:
			return (501);
		default:
			return (500);
	}
}

} // namespace http
