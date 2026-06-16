/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IResourceLocator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 21:48:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/16 19:36:45 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRESOURCELOCATOR_HPP
#define IRESOURCELOCATOR_HPP

#include <string>
#include <vector>

namespace app {
struct SystemResourceInfos;

class IResourceLocator
{
  public:
	virtual ~IResourceLocator(void) {}
	// TODO: id = uri pour marylene,
	virtual SystemResourceInfos locate(
		std::string const &id, std::string const &matchedRoute, std::string const &rootPath
	) const = 0;

	// TODO: id = envoyer SystemResourceInfos du 1er index existant
	virtual SystemResourceInfos locateDefaultIndex(
		std::vector<std::string> const &indexesId,
		std::string const			   &matchedRoute,
		std::string const			   &rootPath
	) const = 0;
};
} // namespace app

#endif // IRESOURCELOCATOR_HPP