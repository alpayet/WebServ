/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResource.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:46:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/09 22:01:09 by alpayet          ###   ########.fr       */
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

#endif // SERVESTATICRESOURCECONTROLLER_HPP