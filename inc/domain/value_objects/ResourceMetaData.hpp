/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceMetaData.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 23:42:18 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/13 02:54:51 by alpayet          ###   ########.fr       */
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
		std::size_t			contentlength
	);

	std::string const &getStoragePath(void) const;
	std::size_t		   getContentLength(void) const;

	bool isExecutable(void) const;
	bool isReadable(void) const;
	bool isCollection(void) const;

  private:
	std::string			_storagePath;
	ResourceType		_type;
	ResourcePermissions _permissions;
	std::size_t			_contentlength;
};
} // namespace domain

#endif // RESOURCEMETADATA_HPP