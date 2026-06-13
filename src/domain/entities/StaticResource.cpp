/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticResource.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 21:45:34 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/13 03:46:38 by alpayet          ###   ########.fr       */
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
	ResourceMetaData const &targetMetaData,
	ResourceMetaData const &indexMetaData
)
	: _id(id), _metaData(targetMetaData)
{
	if (indexMetaData.isCollection())
	{
		if (!indexMetaData.isReadable() || indexMetaData.isCollection())
		{
			if (!isListingEnabled)
				throw Exception(Exception::listingDisabled);
			_intent = generateListing;
			return;
		}
		_metaData = indexMetaData;
		_intent = serveIndex;
	}
	else
		_intent = serveContent;
	if (_metaData.getStoragePath().find(rootPath) != 0)
		throw Exception(Exception::pathTraversalDetected);
	if (!_metaData.isReadable())
		throw Exception(Exception::staticResourceNotReadable);
}

std::string const &StaticResource::getStoragePath(void) const
{
	return (_metaData.getStoragePath());
}

bool StaticResource::shouldServeContent(void) const { return (_intent == serveContent); }

bool StaticResource::shouldServeIndex(void) const { return (_intent == serveIndex); }

bool StaticResource::shouldGenerateListing(void) const { return (_intent == generateListing); }
} // namespace domain
