/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IResourceLocator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 21:48:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/30 17:18:04 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRESOURCELOCATOR_HPP
#define IRESOURCELOCATOR_HPP

#include "domain/enums/ResourcePermissions.hpp"
#include "domain/enums/ResourceType.hpp"
#include <string>
#include <vector>

namespace app {
struct SystemResourceInfo
{
	std::string					resourcePath;
	domain::ResourceType		type;
	domain::ResourcePermissions permissions;
	std::size_t					resourceSize;
	bool						canBeDeleted;
	bool						exists;

	SystemResourceInfo() : resourceSize(0), canBeDeleted(false), exists(false) {};
};

class IResourceLocator
{
  public:
	virtual ~IResourceLocator(void) {}
	virtual SystemResourceInfo locate(
		std::string const &id, std::string const &matchedRoute, std::string const &rootPath
	) const = 0;
	virtual SystemResourceInfo locateDefaultIndex(
		std::vector<std::string> const &indexesId,
		std::string const			   &matchedRoute,
		std::string const			   &rootPath
	) const = 0;
};
} // namespace app

#endif // IRESOURCELOCATOR_HPP