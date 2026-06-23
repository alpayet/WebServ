/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticResource.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 21:45:34 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/22 21:38:16 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/entities/StaticResource.hpp"
#include "domain/Exception.hpp"
#include "domain/value_objects/ResourceMetaData.hpp"

namespace domain {
StaticResource::StaticResource(
	std::string const &id, std::string const &rootPath, ResourceMetaData const &metaData
)
	: _id(id), _metaData(metaData)
{
	if (_metaData.getResourcePath().find(rootPath) != 0)
		throw Exception(Exception::pathTraversalDetected);
}

std::string const &StaticResource::getResourcePath(void) const
{
	return (_metaData.getResourcePath());
}

std::size_t domain::StaticResource::getResourceSize(void) const
{
	return (_metaData.getResourceSize());
}

bool StaticResource::isReadable(void) const { return (_metaData.isReadable()); }

bool StaticResource::isExecutable(void) const { return (_metaData.isExecutable()); }

bool StaticResource::canBeDeleted(void) const
{
	return (_metaData.canBeDeleted() && !_metaData.isCollection());
}
} // namespace domain
