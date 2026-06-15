/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 01:38:03 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/15 01:52:00 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTROUTER_HPP
#define HTTPROUTER_HPP

namespace http {
class IRouteRegistry;
class ServeStaticResourceController;
class DeleteStaticResourceController;
class ExecuteDynamicResourceController;
class Request;
class Response;

class Router
{
  public:
	Router(
		IRouteRegistry					 &routeRegistry,
		ServeStaticResourceController	 &serveStaticResourceController,
		DeleteStaticResourceController	 &deleteStaticResourceController,
		ExecuteDynamicResourceController &executeDynamicResourceController
	);

	void route(Request const &request, Response &response);

  private:
	Router(Router const &src);
	Router &operator=(Router const &rhs);

	IRouteRegistry &_routeRegistry;

	ServeStaticResourceController	 &_serveStaticResourceController;
	DeleteStaticResourceController	 &_deleteStaticResourceController;
	ExecuteDynamicResourceController &_executeDynamicResourceController;
};
} // namespace http

#endif // HTTPROUTER_HPP