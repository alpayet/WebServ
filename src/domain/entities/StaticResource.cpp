/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticResource.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 21:45:34 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:13:37 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/entities/StaticResource.hpp"
#include "domain/Exception.hpp"

namespace domain {
StaticResource::StaticResource(
	std::string const  &id,
	std::string const	rootPath,
	std::string const  &storagePath,
	ResourceType		type,
	ResourcePermissions permissions,
	std::size_t			contentLenght
)
	: _id(id), _contentLenght(contentLenght)
{
	if (storagePath.find(rootPath) != 0)
		throw domain::Exception(domain::Exception::PathTraversalDetected);
}

// std::string			_id;
// std::string			_storagePath;
// HandlingIntent		_intent;
// std::size_t			_contentLenght;
// ResourcePermissions _permission;

std::string const &StaticResource::getId(void) const { return (_id); }

std::string const &StaticResource::getStoragePath(void) const { return (_storagePath); }
} // namespace domain
