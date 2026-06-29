/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 01:38:03 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/30 00:23:04 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTROUTER_HPP
#define HTTPROUTER_HPP

namespace http {
class IRouteRegistry;
class ServeStaticResourceController;
class DeleteStaticResourceController;
class ExecuteDynamicResourceController;
class Context;

class Router
{
  public:
	Router(
		IRouteRegistry				   &routeRegistry,
		ServeStaticResourceController  &serveStaticResourceController,
		DeleteStaticResourceController &deleteStaticResourceController
		// ExecuteDynamicResourceController &executeDynamicResourceController
	);

	void route(Context &context);

  private:
	Router(Router const &src);
	Router &operator=(Router const &rhs);

	IRouteRegistry &_routeRegistry;

	ServeStaticResourceController  &_serveStaticResourceController;
	DeleteStaticResourceController &_deleteStaticResourceController;
	// ExecuteDynamicResourceController &_executeDynamicResourceController;
};
} // namespace http

#endif // HTTPROUTER_HPP