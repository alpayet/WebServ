/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IResourceLocator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 04:11:57 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/03 01:24:36 by alpayet          ###   ########.fr       */
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
};

#endif // IRESOURCELOCATOR_HPP