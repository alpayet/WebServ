/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRouteRegistry.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 10:04:24 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/15 03:15:31 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IROUTEREGISTRY_HPP
#define IROUTEREGISTRY_HPP

#include <string>

namespace http {
// TODO: faire herité la config de cette interface
struct RoutePolicy;

class IRouteRegistry
{
  public:
	virtual ~IRouteRegistry(void) {}
	// TODO: id = uri pour marylene
	// TODO: if return, throw at the beginning
	virtual RoutePolicy match(std::string const &uri) = 0;
};
} // namespace http

#endif // IROUTEREGISTRY_HPP