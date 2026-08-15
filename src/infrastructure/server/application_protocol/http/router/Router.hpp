/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 01:38:03 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:19:53 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPROUTER_HPP
#define HTTPROUTER_HPP

namespace webserv {
namespace http {
class IRouteRegistry;
struct Context;

namespace controller {
class ServeStaticResource;
class DeleteStaticResource;
class ExecuteDynamicResource;
} // namespace controller

class Router
{
  public:
	Router(
		IRouteRegistry const			   &routeRegistry,
		controller::ServeStaticResource	   &serveStaticResource,
		controller::DeleteStaticResource   &deleteStaticResource,
		controller::ExecuteDynamicResource &executeDynamicResource
	);

	void route(Context &context);

  private:
	Router(Router const &src);
	Router &operator=(Router const &rhs);

	IRouteRegistry const &_routeRegistry;

	controller::ServeStaticResource	   &_serveStaticResource;
	controller::DeleteStaticResource   &_deleteStaticResource;
	controller::ExecuteDynamicResource &_executeDynamicResource;
};
} // namespace http
}

#endif // HTTPROUTER_HPP
