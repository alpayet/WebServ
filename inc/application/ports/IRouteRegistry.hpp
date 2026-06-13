/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRouteRegistry.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 10:04:24 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/13 02:29:55 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IROUTEREGISTRY_HPP
#define IROUTEREGISTRY_HPP

#include <string>

// TODO: faire herité la config de cette interface
namespace app {
struct RoutePolicy;

class IRouteRegistry
{
  public:
	virtual ~IRouteRegistry(void) {}

	virtual RoutePolicy match(std::string const &id) = 0;
};
} // namespace app

#endif // IROUTEREGISTRY_HPP