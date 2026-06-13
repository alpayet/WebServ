/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResourceController.hpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:46:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:23:07 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FINDSTATICRESOURCECONTROLLER_HPP
#define FINDSTATICRESOURCECONTROLLER_HPP

namespace useCase {
class FindStaticResource;
} // namespace useCase

namespace http {
class Request;
class Response;

class FindStaticResourceController
{
  public:
	FindStaticResourceController(app::useCase::FindStaticResource &useCase);

	void FindStaticResourceController::operator()(
		Request const &request, Response &response, app::RoutePolicy const &routePolicy
	);

  private:
	FindStaticResourceController(FindStaticResourceController const &src);
	FindStaticResourceController &operator=(FindStaticResourceController const &rhs);

	app::useCase::FindStaticResource &_useCase;
};
} // namespace http

#endif // FINDSTATICRESOURCECONTROLLER_HPP