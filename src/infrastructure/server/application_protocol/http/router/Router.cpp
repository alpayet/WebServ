/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 01:50:14 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:19:41 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/router/Router.hpp"
#include "infrastructure/server/application_protocol/http/controllers/DeleteStaticResource.hpp"
#include "infrastructure/server/application_protocol/http/controllers/ExecuteDynamicResource.hpp"
#include "infrastructure/server/application_protocol/http/controllers/ServeStaticResource.hpp"
#include "infrastructure/server/application_protocol/http/core/Context.hpp"
#include "infrastructure/server/application_protocol/http/exceptions/Exception.hpp"
#include "infrastructure/server/application_protocol/http/exceptions/ReturnException.hpp"
#include "infrastructure/server/application_protocol/http/methods.hpp"
#include "infrastructure/server/application_protocol/http/request/Request.hpp"
#include "infrastructure/server/application_protocol/http/router/IRouteRegistry.hpp"
#include "infrastructure/server/application_protocol/http/router/RoutePolicy.hpp"
#include <algorithm>

namespace webserv {
namespace http {
Router::Router(
	IRouteRegistry const			   &routeRegistry,
	controller::ServeStaticResource	   &serveStaticResource,
	controller::DeleteStaticResource   &deleteStaticResource,
	controller::ExecuteDynamicResource &executeDynamicResource
)
	: _routeRegistry(routeRegistry), _serveStaticResource(serveStaticResource),
	  _deleteStaticResource(deleteStaticResource), _executeDynamicResource(executeDynamicResource)
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

	if (route_policy.isCgi)
		_executeDynamicResource(context, route_policy);
	else if (method == GET)
		_serveStaticResource(context, route_policy);
	else if (method == DELETE)
		_deleteStaticResource(context, route_policy);
}
} // namespace http
} // namespace webserv
