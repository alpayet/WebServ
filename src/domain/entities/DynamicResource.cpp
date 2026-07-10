/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DynamicResource.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:18:21 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/01 04:12:57 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/entities/DynamicResource.hpp"
#include "domain/Exception.hpp"
#include "domain/value_objects/ResourceMetaData.hpp"

namespace domain {
DynamicResource::DynamicResource(std::string const &id, ResourceMetaData const &metaData)
	: _id(id), _metaData(metaData)
{}

std::string const &DynamicResource::getResourcePath(void) const
{
	return (_metaData.getResourcePath());
}

bool DynamicResource::isReadable(void) const { return (_metaData.isReadable()); }

bool DynamicResource::isExecutable(void) const { return (_metaData.isExecutable()); }

} // namespace domain
