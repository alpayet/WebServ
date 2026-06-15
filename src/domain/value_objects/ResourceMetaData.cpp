/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceMetaData.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 23:55:19 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/15 23:42:23 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/value_objects/ResourceMetaData.hpp"
#include "domain/Exception.hpp"

namespace domain {
ResourceMetaData::ResourceMetaData(
	std::string			resourcePath,
	ResourceType		type,
	ResourcePermissions permissions,
	std::size_t			contentlength,
	bool				canBeDeleted
)
	: _permissions(permissions), _contentlength(contentlength), _canBeDeleted(canBeDeleted)
{
	if (_resourcePath.empty())
		throw Exception(Exception::pathMissing);
	_resourcePath = resourcePath;
	if (type == unknown)
		throw Exception(Exception::typeUnsupported);
	_type = type;
}

std::string const &ResourceMetaData::getResourcePath(void) const { return (_resourcePath); }

std::size_t ResourceMetaData::getContentLength(void) const { return (_contentlength); }

bool ResourceMetaData::isExecutable(void) const { return (_permissions & executable); }

bool ResourceMetaData::isReadable(void) const { return (_permissions & readable); }

bool ResourceMetaData::isCollection(void) const { return (_type == collection); }

bool ResourceMetaData::canBeDeleted() const { return (_canBeDeleted); }

} // namespace domain
