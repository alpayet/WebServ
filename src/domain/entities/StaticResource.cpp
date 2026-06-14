/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticResource.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 21:45:34 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/14 01:49:42 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/entities/StaticResource.hpp"
#include "domain/Exception.hpp"
#include "domain/value_objects/ResourceMetaData.hpp"

namespace domain {
StaticResource::StaticResource(
	std::string const	   &id,
	std::string const	   &rootPath,
	bool const				isListingEnabled,
	ResourceMetaData const &targetMetaData
)
	: _id(id), _metaData(targetMetaData)
{
	if (targetMetaData.isCollection())
	{
		if (!isListingEnabled)
			throw Exception(Exception::listingDisabled);
		_intent = generateListing;
	}
	else
		_intent = serveContent;
	if (_metaData.getStoragePath().find(rootPath) != 0)
		throw Exception(Exception::pathTraversalDetected);
}

StaticResource::StaticResource(
	std::string const	   &id,
	std::string const	   &rootPath,
	bool const				isListingEnabled,
	ResourceMetaData const &targetMetaData,
	ResourceMetaData const &indexMetaData
)
	: _id(id), _metaData(targetMetaData)
{
	if (targetMetaData.isCollection())
	{
		if (indexMetaData.isReadable() && !indexMetaData.isCollection())
		{
			_metaData = indexMetaData;
			_intent = serveIndex;
		}
		else
		{
			if (!isListingEnabled)
				throw Exception(Exception::listingDisabled);
			_intent = generateListing;
		}
	}
	else
		_intent = serveContent;
	if (_metaData.getStoragePath().find(rootPath) != 0)
		throw Exception(Exception::pathTraversalDetected);
}

bool StaticResource::shouldServeContent(void) const { return (_intent == serveContent); }

bool StaticResource::shouldServeIndex(void) const { return (_intent == serveIndex); }

bool StaticResource::shouldGenerateListing(void) const { return (_intent == generateListing); }

std::string const &StaticResource::getStoragePath(void) const
{
	return (_metaData.getStoragePath());
}

bool StaticResource::isReadable(void) const { return (_metaData.isReadable()); }

bool StaticResource::canBeDeleted(void) const
{
	if (!_metaData.canBeDeleted())
		return (false);
	if (_metaData.isCollection())
		return (false);
}
} // namespace domain
