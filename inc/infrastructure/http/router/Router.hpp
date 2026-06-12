/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 01:38:03 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:30:53 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTROUTER_HPP
#define HTTPROUTER_HPP

namespace app {
class IRouteRegistry;
} // namespace app

namespace http {
class FindStaticResourceController;
class DeleteStaticResourceController;
class ExecuteDynamicResourceController;
class Request;
class Response;

class Router
{
  public:
	Router(
		app::IRouteRegistry				 &routeRegistry,
		FindStaticResourceController	 &findStaticResourceController,
		DeleteStaticResourceController	 &deleteStaticResourceController,
		ExecuteDynamicResourceController &executeDynamicResourceController
	);

	void route(Request const &request, Response &response);

  private:
	Router(Router const &src);
	Router &operator=(Router const &rhs);

	app::IRouteRegistry &_routeRegistry;

	FindStaticResourceController	 &_findStaticResourceController;
	DeleteStaticResourceController	 &_deleteStaticResourceController;
	ExecuteDynamicResourceController &_executeDynamicResourceController;
};
} // namespace http

#endif // HTTPROUTER_HPP