/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DynamicResource.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:18:21 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/15 01:20:09 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/entities/DynamicResource.hpp"
#include "domain/Exception.hpp"
#include "domain/value_objects/ResourceMetaData.hpp"

namespace domain {
DynamicResource::DynamicResource(
	std::string const &id, std::string const &rootPath, ResourceMetaData const &metaData
)
	: _id(id), _metaData(metaData)
{
	if (_metaData.getStoragePath().find(rootPath) != 0)
		throw Exception(Exception::pathTraversalDetected);
}

std::string const &DynamicResource::getStoragePath(void) const
{
	return (_metaData.getStoragePath());
}

bool DynamicResource::isReadable(void) const { return (_metaData.isReadable()); }

bool DynamicResource::isExecutable(void) const { return (_metaData.isExecutable()); }

bool DynamicResource::canBeDeleted(void) const
{
	return (_metaData.canBeDeleted() && !_metaData.isCollection());
}
} // namespace domain
