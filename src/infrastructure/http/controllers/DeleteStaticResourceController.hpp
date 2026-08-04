/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResourceController.hpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:46:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/04 15:51:29 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETESTATICRESOURCECONTROLLER_HPP
#define DELETESTATICRESOURCECONTROLLER_HPP

namespace app {
namespace useCase {
class DeleteStaticResource;
} // namespace useCase
} // namespace app

namespace http {
struct Context;
struct RoutePolicy;

class DeleteStaticResourceController
{
  public:
	DeleteStaticResourceController(app::useCase::DeleteStaticResource &useCase);

	void operator()(Context &context, RoutePolicy const &routePolicy);

  private:
	DeleteStaticResourceController(DeleteStaticResourceController const &src);
	DeleteStaticResourceController &operator=(DeleteStaticResourceController const &rhs);

	app::useCase::DeleteStaticResource &_useCase;
};
} // namespace http

#endif // DELETESTATICRESOURCECONTROLLER_HPP