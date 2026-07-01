/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 01:50:14 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/01 02:14:47 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/router/Router.hpp"
#include "infrastructure/http/Context.hpp"
#include "infrastructure/http/controllers/DeleteStaticResourceController.hpp"
#include "infrastructure/http/controllers/ExecuteDynamicResourceController.hpp"
#include "infrastructure/http/controllers/ServeStaticResourceController.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"
#include "infrastructure/http/methods.hpp"
#include "infrastructure/http/request/Request.hpp"
#include "infrastructure/http/router/IRouteRegistry.hpp"
#include "infrastructure/http/router/RoutePolicy.hpp"
#include <algorithm>

namespace http {
Router::Router(
	IRouteRegistry				   &routeRegistry,
	ServeStaticResourceController  &serveStaticResourceController,
	DeleteStaticResourceController &deleteStaticResourceController
	// ExecuteDynamicResourceController &executeDynamicResourceController
)
	: _routeRegistry(routeRegistry), _serveStaticResourceController(serveStaticResourceController),
	  _deleteStaticResourceController(deleteStaticResourceController)
//   _executeDynamicResourceController(executeDynamicResourceController)
{}

void Router::route(Context &context)
{
	RoutePolicy const &route_policy = _routeRegistry.match(context.input.state.request.target);
	std::vector<std::string> const &allowed_methods = route_policy.allowedMethods;
	std::string const			   &method = context.input.state.request.method;

	if (std::find(allowed_methods.begin(), allowed_methods.end(), method) == allowed_methods.end())
		throw Exception(Exception::methodNotAllowed);

	if (method == GET)
		_serveStaticResourceController(context, route_policy);
	if (method == DELETE)
		_deleteStaticResourceController(context, route_policy);
}
} // namespace http
