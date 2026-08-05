/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 01:38:03 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/04 15:51:29 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPROUTER_HPP
#define HTTPROUTER_HPP

namespace http {
class IRouteRegistry;
class ServeStaticResourceController;
class DeleteStaticResourceController;
class ExecuteDynamicResourceController;
struct Context;

class Router
{
  public:
	Router(
		const IRouteRegistry				   &routeRegistry,
		ServeStaticResourceController  &serveStaticResourceController,
		DeleteStaticResourceController &deleteStaticResourceController
		// ExecuteDynamicResourceController &executeDynamicResourceController
	);

	void route(Context &context);

  private:
	Router(Router const &src);
	Router &operator=(Router const &rhs);

	const IRouteRegistry &_routeRegistry;

	ServeStaticResourceController  &_serveStaticResourceController;
	DeleteStaticResourceController &_deleteStaticResourceController;
	// ExecuteDynamicResourceController &_executeDynamicResourceController;
};
} // namespace http

#endif // HTTPROUTER_HPP