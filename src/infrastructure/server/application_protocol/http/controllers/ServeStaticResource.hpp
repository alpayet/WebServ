/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResource.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:46:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:09:34 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVESTATICRESOURCECONTROLLER_HPP
#define SERVESTATICRESOURCECONTROLLER_HPP

namespace webserv {
namespace app {
namespace useCase {
class ServeStaticResource;
} // namespace useCase
} // namespace app

namespace http {
struct Context;
struct RoutePolicy;

namespace controller {
class ServeStaticResource
{
  public:
	ServeStaticResource(app::useCase::ServeStaticResource &useCase);

	void operator()(Context &context, RoutePolicy const &routePolicy);

  private:
	ServeStaticResource(ServeStaticResource const &src);
	ServeStaticResource &operator=(ServeStaticResource const &rhs);

	app::useCase::ServeStaticResource &_useCase;
};
} // namespace controller
} // namespace http
} // namespace webserv

#endif // SERVESTATICRESOURCECONTROLLER_HPP