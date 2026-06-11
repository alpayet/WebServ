/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 01:38:03 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/11 17:42:24 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTROUTER_HPP
#define HTTPROUTER_HPP

class IRouteRegistry;

namespace http
{
	class FindStaticResourceController;
	class DeleteStaticResourceController;
	class ExecuteDynamicResourceController;
	class Request;
	class Response;

	class Router
	{
	  public:
		Router(
			IRouteRegistry					 &routeRegistry,
			FindStaticResourceController	 &findStaticResourceController,
			DeleteStaticResourceController	 &deleteStaticResourceController,
			ExecuteDynamicResourceController &executeDynamicResourceController
		);

		void route(Request const &request, Response &response);

	  private:
		Router(Router const &src);
		Router &operator=(Router const &rhs);

		IRouteRegistry &_routeRegistry;

		FindStaticResourceController	 &_findStaticResourceController;
		DeleteStaticResourceController	 &_deleteStaticResourceController;
		ExecuteDynamicResourceController &_executeDynamicResourceController;
	};
} // namespace http

#endif // HTTPROUTER_HPP