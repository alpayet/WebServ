/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticResource.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 21:45:34 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/14 15:10:36 by alpayet          ###   ########.fr       */
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
	if (_metaData.getStoragePath().find(rootPath) != 0)
		throw Exception(Exception::pathTraversalDetected);
}

std::string const &StaticResource::getStoragePath(void) const
{
	return (_metaData.getStoragePath());
}

bool StaticResource::isReadable(void) const { return (_metaData.isReadable()); }

bool StaticResource::isExecutable(void) const { return (_metaData.isExecutable()); }

bool StaticResource::canBeDeleted(void) const
{
	if (!_metaData.canBeDeleted())
		return (false);
	if (_metaData.isCollection())
		return (false);
}
} // namespace domain
