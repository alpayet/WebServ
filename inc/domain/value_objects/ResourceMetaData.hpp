/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceMetaData.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 23:42:18 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/14 00:47:09 by alpayet          ###   ########.fr       */
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
		std::string			storagePath,
		ResourceType		type,
		ResourcePermissions permissions,
		std::size_t			contentlength,
		bool				canBeDeleted
	);

	std::string const &getStoragePath(void) const;
	std::size_t		   getContentLength(void) const;

	bool isExecutable(void) const;
	bool isReadable(void) const;
	bool isCollection(void) const;

	bool canBeDeleted(void) const;

  private:
	std::string			_storagePath;
	ResourceType		_type;
	ResourcePermissions _permissions;
	std::size_t			_contentlength;
	bool				_canBeDeleted;
};
} // namespace domain

#endif // RESOURCEMETADATA_HPP