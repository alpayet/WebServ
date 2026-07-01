/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorLookup.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 04:00:23 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/01 04:27:45 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/exceptions/errorLookup.hpp"

namespace http {
unsigned short toHttpStatusCode(Exception::ErrorCode const errorCode)
{
	switch (errorCode)
	{
		case Exception::invalidLineBreak:
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
			return (400);
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
		default:
			return (500);
	}
}

unsigned short toHttpStatusCode(app::Exception::ErrorCode errorCode)
{
	switch (errorCode)
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

unsigned short toHttpStatusCode(domain::Exception::ErrorCode const errorCode)
{
	switch (errorCode)
	{
		case domain::Exception::pathMissing:
			return (404);
		case domain::Exception::typeUnsupported:
			return (501);
		default:
			return (500);
	}
}

unsigned short toHttpStatusCode(fileSystem::Exception::ErrorCode const errorCode) { return (500); }

} // namespace http
