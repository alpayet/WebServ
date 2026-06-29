/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourceController.hpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:46:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/29 19:52:11 by alpayet          ###   ########.fr       */
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
class Context;
struct RoutePolicy;

class ServeStaticResourceController
{
  public:
	ServeStaticResourceController(app::useCase::ServeStaticResource &useCase);

	void operator()(Context &context, RoutePolicy const &routePolicy);

  private:
	ServeStaticResourceController(ServeStaticResourceController const &src);
	ServeStaticResourceController &operator=(ServeStaticResourceController const &rhs);

	app::useCase::ServeStaticResource &_useCase;
};
} // namespace http

#endif // SERVESTATICRESOURCECONTROLLER_HPP