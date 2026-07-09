/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_lookup.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 04:00:23 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/09 03:52:01 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/exceptions/error_lookup.hpp"

namespace http {
unsigned short to_status_code(Exception::ErrorCode error_code)
{
	switch (error_code)
	{
		case Exception::lineBreakInvalid:
			return (400);
		case Exception::requestLineMalformed:
			return (400);
		case Exception::headerLineMalformed:
			return (400);
		case Exception::methodInvalid:
			return (400);
		case Exception::methodNotAllowed:
			return (405);
		case Exception::targetInvalid:
			return (400);
		case Exception::versionInvalid:
			return (505);
		case Exception::headerKeyInvalid:
			return (400);
		case Exception::headerValueInvalid:
			return (400);
		case Exception::contentLengthInvalid:
			return (400);
		case Exception::contentLengthRequired:
			return (411);
		case Exception::requestLineTooLarge:
			return (414);
		case Exception::headerLineTooLarge:
			return (431);
		case Exception::headerCountTooLarge:
			return (431);
		case Exception::bodyTooLarge:
			return (413);
		case Exception::maxLocalRedirDepthExceeded:
			return (500);
		case Exception::timeOut:
			return (408);
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
		case cgi::Exception::documentResponseMalformed:
		case cgi::Exception::localRedirResponseMalformed:
		case cgi::Exception::clientRedirResponseMalformed:
		case cgi::Exception::clientRedirDocResponseMalformed:
		case cgi::Exception::statusCodeInvalid:
		case cgi::Exception::statusReasonInvalid:
		case cgi::Exception::locationInvalid:
		case cgi::Exception::lineBreakInvalid:
		case cgi::Exception::headerLineMalformed:
		case cgi::Exception::headerKeyInvalid:
		case cgi::Exception::headerValueInvalid:
		case cgi::Exception::contentLengthInvalid:
		case cgi::Exception::headerLineTooLarge:
		case cgi::Exception::headerCountTooLarge:
		case cgi::Exception::bodyTooLarge:
		case cgi::Exception::bodySizeMismatch:
		case cgi::Exception::prematureEof:
			return (502);
		case cgi::Exception::timeOut:
			return (504);
		default:
			return (500);
	}
}

unsigned short to_status_code(app::Exception::ErrorCode error_code)
{
	switch (error_code)
	{
		case app::Exception::accessDenied:
			return (403);
		case app::Exception::notFound:
			return (404);
		case app::Exception::listingDisabled:
			return (403);
		case app::Exception::deleteFailed:
			return (500);
		case app::Exception::pathTraversalDetected:
			return (400);
		default:
			return (500);
	}
}

unsigned short to_status_code(domain::Exception::ErrorCode error_code)
{
	switch (error_code)
	{
		case domain::Exception::pathMissing:
			return (404);
		case domain::Exception::typeUnsupported:
			return (501);
		default:
			return (500);
	}
}

} // namespace http
