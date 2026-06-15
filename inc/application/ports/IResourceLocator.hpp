/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IResourceLocator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 21:48:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/15 14:56:01 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRESOURCELOCATOR_HPP
#define IRESOURCELOCATOR_HPP

#include <string>
#include <vector>

// TODO: faire herité la config de cette interface
namespace app {
struct SystemResourceInfos;

class IResourceLocator
{
  public:
	virtual ~IResourceLocator(void) {}
	// TODO: id = uri
	virtual SystemResourceInfos
	locate(std::string const &id, std::string const &rootPath) const = 0;

	// TODO: id = envoyer SystemResourceInfos du 1er index existant
	virtual SystemResourceInfos
	locateDefaultIndex(std::vector<std::string> indexesId, std::string const &rootPath) const = 0;
};
} // namespace app

#endif // IRESOURCELOCATOR_HPP