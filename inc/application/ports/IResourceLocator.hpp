/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IResourceLocator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 21:48:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/13 03:32:44 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRESOURCELOCATOR_HPP
#define IRESOURCELOCATOR_HPP

#include <string>

// TODO: faire herité la config de cette interface
namespace app {
struct SystemResourceInfos;

class IResourceLocator
{
  public:
	virtual ~IResourceLocator(void) {}

	virtual SystemResourceInfos
	locate(std::string const &id, std::string const &rootPath) const = 0;

	virtual SystemResourceInfos
	locate_index(std::string const &index_id, std::string const &rootPath) const = 0;
};
} // namespace app

#endif // IRESOURCELOCATOR_HPP