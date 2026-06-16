/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceMetaData.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 23:55:19 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/16 16:47:44 by mlouis           ###   ########.fr       */
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
	: _permissions(permissions), _contentLength(contentlength), _canBeDeleted(canBeDeleted)
{
	if (_resourcePath.empty())
		throw Exception(Exception::pathMissing);
	_resourcePath = resourcePath;
	if (type == unknown)
		throw Exception(Exception::typeUnsupported);
	_type = type;
}

std::string const &ResourceMetaData::getResourcePath(void) const { return (_resourcePath); }

std::size_t ResourceMetaData::getContentLength(void) const { return (_contentLength); }

bool ResourceMetaData::isExecutable(void) const { return (_permissions & executable); }

bool ResourceMetaData::isReadable(void) const { return (_permissions & readable); }

bool ResourceMetaData::isCollection(void) const { return (_type == collection); }

bool ResourceMetaData::canBeDeleted() const { return (_canBeDeleted); }

} // namespace domain
