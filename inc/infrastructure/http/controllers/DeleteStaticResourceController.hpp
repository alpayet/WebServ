/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResourceController.hpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:46:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:22:49 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETESTATICRESOURCECONTROLLER_HPP
#define DELETESTATICRESOURCECONTROLLER_HPP

namespace useCase {
class DeleteStaticResource;
} // namespace useCase

namespace http {
class Request;
class Response;

class DeleteStaticResourceController
{
  public:
	DeleteStaticResourceController(app::useCase::DeleteStaticResource &useCase);

	void DeleteStaticResourceController::operator()(
		Request const &request, Response &response, app::RoutePolicy const &routePolicy
	);

  private:
	DeleteStaticResourceController(DeleteStaticResourceController const &src);
	DeleteStaticResourceController &operator=(DeleteStaticResourceController const &rhs);

	app::useCase::DeleteStaticResource &_useCase;
};
} // namespace http

#endif // DELETESTATICRESOURCECONTROLLER_HPP