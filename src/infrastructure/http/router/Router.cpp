/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 01:50:14 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/11 17:47:07 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/router/Router.hpp"
#include "application/ports/IRouteRegistry.hpp"
#include "application/ports/RoutePolicy.hpp"
#include "infrastructure/http/Request.hpp"
#include "infrastructure/http/Response.hpp"
#include "infrastructure/http/controllers/DeleteStaticResourceController.hpp"
#include "infrastructure/http/controllers/ExecuteDynamicResourceController.hpp"
#include "infrastructure/http/controllers/FindStaticResourceController.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"
#include <algorithm>

namespace http
{
	Router::Router(
		IRouteRegistry					 &routeRegistry,
		FindStaticResourceController	 &findStaticResourceController,
		DeleteStaticResourceController	 &deleteStaticResourceController,
		ExecuteDynamicResourceController &executeDynamicResourceController
	)
		: _routeRegistry(routeRegistry),
		  _findStaticResourceController(findStaticResourceController),
		  _deleteStaticResourceController(deleteStaticResourceController),
		  _executeDynamicResourceController(executeDynamicResourceController)
	{
	}

	void Router::route(Request const &request, Response &response)
	{
		RoutePolicy const			   &route_policy = _routeRegistry.match(request.target);
		std::vector<std::string> const &allowed_methods = route_policy.allowedMethods;
		std::string const			   &method = request.method;

		if (std::find(allowed_methods.begin(), allowed_methods.end(), method) ==
			allowed_methods.end())
			throw Exception(Exception::methodNotAllowed);

		if (method == "GET")
			_findStaticResourceController(request, response, route_policy);
		if (method == "DELETE")
			_deleteStaticResourceController(request, response, route_policy);
	}
} // namespace http
