/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourceController.hpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:46:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/25 19:51:19 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVESTATICRESOURCECONTROLLER_HPP
#define SERVESTATICRESOURCECONTROLLER_HPP

namespace app {
namespace useCase {
class ServeStaticResource;
} // namespace useCase
} // namespace app

namespace http {
class Request;
class Context;
struct RoutePolicy;

class ServeStaticResourceController
{
  public:
	ServeStaticResourceController(
		app::useCase::ServeStaticResource &useCase, IVersionProvider &versionProvider
	);

	void
	ServeStaticResourceController::operator()(Context &context, RoutePolicy const &routePolicy);

  private:
	ServeStaticResourceController(ServeStaticResourceController const &src);
	ServeStaticResourceController &operator=(ServeStaticResourceController const &rhs);

	app::useCase::ServeStaticResource &_useCase;
};
} // namespace http

#endif // SERVESTATICRESOURCECONTROLLER_HPP