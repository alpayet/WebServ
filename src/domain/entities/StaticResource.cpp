/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticResource.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 21:45:34 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:35:01 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/entities/StaticResource.hpp"
#include "domain/Exception.hpp"
#include "domain/value_objects/ResourceMetaData.hpp"

namespace webserv {
namespace domain {
StaticResource::StaticResource(std::string const &id, ResourceMetaData const &metaData)
	: _id(id), _metaData(metaData)
{}

std::string const &StaticResource::StaticResource::getId(void) const { return (_id); }

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
}
