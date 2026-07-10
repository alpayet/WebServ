/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRouteRegistry.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 10:04:24 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/17 09:56:08 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IROUTEREGISTRY_HPP
#define IROUTEREGISTRY_HPP

#include <string>

namespace http {
struct RoutePolicy;

class IRouteRegistry
{
  public:
	virtual ~IRouteRegistry(void) {}
	virtual RoutePolicy match(std::string const &uri) const = 0;
};
} // namespace http

#endif // IROUTEREGISTRY_HPP