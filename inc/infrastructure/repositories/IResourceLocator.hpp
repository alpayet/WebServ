/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IResourceLocator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 04:11:57 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/05 14:08:55 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRESOURCELOCATOR_HPP
#define IRESOURCELOCATOR_HPP

#include <string>

// TODO: faire herité la config de cette interface
class IResourceLocator
{
  public:
	virtual ~IResourceLocator(void) {}

	virtual std::string resolvePhysicalPath(std::string const &uri) const = 0;
	// TODO: throw http if repo
};

#endif // IRESOURCELOCATOR_HPP