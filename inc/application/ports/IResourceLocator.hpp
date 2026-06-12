/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IResourceLocator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 21:48:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:07:32 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRESOURCELOCATOR_HPP
#define IRESOURCELOCATOR_HPP

#include <string>

namespace app {
struct SystemResourceInfo;
// TODO: faire herité la config de cette interface

class IResourceLocator
{
  public:
	virtual ~IResourceLocator(void) {}

	virtual SystemResourceInfo locate(std::string const &id, std::string const &rootPath) const = 0;
};
} // namespace app

#endif // IRESOURCELOCATOR_HPP