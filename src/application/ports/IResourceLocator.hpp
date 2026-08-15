/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IResourceLocator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 21:48:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:37:20 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRESOURCELOCATOR_HPP
#define IRESOURCELOCATOR_HPP

#include "application/ports/SystemResourceInfo.hpp"
#include "domain/enums/ResourcePermissions.hpp"
#include "domain/enums/ResourceType.hpp"
#include <string>
#include <vector>

namespace webserv {
namespace app {
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
} // namespace webserv

#endif // IRESOURCELOCATOR_HPP