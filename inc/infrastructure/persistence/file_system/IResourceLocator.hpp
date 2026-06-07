/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IResourceLocator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 04:11:57 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/07 03:40:09 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILESYSTEMIRESOURCELOCATOR_HPP
#define FILESYSTEMIRESOURCELOCATOR_HPP

#include <string>

// TODO: faire herité la config de cette interface
namespace fileSystem
{
	class IResourceLocator
	{
	  public:
		virtual ~IResourceLocator(void) {}

		virtual std::string resolvePhysicalPath(std::string const &uri) const = 0;
	};
} // namespace fileSystem

#endif // FILESYSTEMIRESOURCELOCATOR_HPP