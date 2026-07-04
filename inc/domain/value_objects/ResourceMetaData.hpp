/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceMetaData.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 23:42:18 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/04 22:34:57 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCEMETADATA_HPP
#define RESOURCEMETADATA_HPP

#include "domain/enums/ResourcePermissions.hpp"
#include "domain/enums/ResourceType.hpp"
#include <string>

namespace domain {
class ResourceMetaData
{
  public:
	ResourceMetaData(
		std::string const  &resourcePath,
		ResourceType		type,
		ResourcePermissions permissions,
		std::size_t			resourceSize,
		bool				canBeDeleted
	);

	std::string const &getResourcePath(void) const;
	std::size_t		   getResourceSize(void) const;

	bool isExecutable(void) const;
	bool isReadable(void) const;
	bool isCollection(void) const;

	bool canBeDeleted(void) const;

  private:
	std::string			_resourcePath;
	ResourceType		_type;
	ResourcePermissions _permissions;
	std::size_t			_resourceSize;
	bool				_canBeDeleted;
};
} // namespace domain

#endif // RESOURCEMETADATA_HPP