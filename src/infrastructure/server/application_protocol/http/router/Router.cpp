/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 01:50:14 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/05 03:38:26 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/router/Router.hpp"
#include "infrastructure/server/application_protocol/http/controllers/DeleteStaticResourceController.hpp"
#include "infrastructure/server/application_protocol/http/controllers/ExecuteDynamicResourceController.hpp"
#include "infrastructure/server/application_protocol/http/controllers/ServeStaticResourceController.hpp"
#include "infrastructure/server/application_protocol/http/core/Context.hpp"
#include "infrastructure/server/application_protocol/http/exceptions/Exception.hpp"
#include "infrastructure/server/application_protocol/http/exceptions/ReturnException.hpp"
#include "infrastructure/server/application_protocol/http/methods.hpp"
#include "infrastructure/server/application_protocol/http/request/Request.hpp"
#include "infrastructure/server/application_protocol/http/router/IRouteRegistry.hpp"
#include "infrastructure/server/application_protocol/http/router/RoutePolicy.hpp"
#include <algorithm>

namespace http {
Router::Router(
	IRouteRegistry const		   &routeRegistry,
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
	Request const	  &request = context.input.state.request;
	std::string const &method = request.getMethod();

	RoutePolicy const			   &route_policy = _routeRegistry.match(request.getTarget());
	std::vector<std::string> const &allowed_methods = route_policy.allowedMethods;

	if (route_policy.hasReturn)
		throw ReturnException(route_policy.returnCode);
	if (std::find(allowed_methods.begin(), allowed_methods.end(), method) == allowed_methods.end())
		throw Exception(Exception::METHOD_NOT_ALLOWED);

	// if (route_policy.isCgi)
	// 	_executeDynamicResourceController(context, route_policy);
	else if (method == GET)
		_serveStaticResourceController(context, route_policy);
	else if (method == DELETE)
		_deleteStaticResourceController(context, route_policy);
}
} // namespace http
