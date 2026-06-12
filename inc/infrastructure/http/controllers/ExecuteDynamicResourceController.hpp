/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceController.hpp               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:46:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:22:59 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTEDYNAMICRESOURCECONTROLLER_HPP
#define EXECUTEDYNAMICRESOURCECONTROLLER_HPP

namespace useCase {
class ExecuteDynamicResource;
} // namespace useCase

namespace http {
class Request;
class Response;

class ExecuteDynamicResourceController
{
  public:
	ExecuteDynamicResourceController(app::useCase::ExecuteDynamicResource &useCase);

	void ExecuteDynamicResourceController::operator()(
		Request const &request, Response &response, app::RoutePolicy const &routePolicy
	);

  private:
	ExecuteDynamicResourceController(ExecuteDynamicResourceController const &src);
	ExecuteDynamicResourceController &operator=(ExecuteDynamicResourceController const &rhs);

	app::useCase::ExecuteDynamicResource &_useCase;
};
} // namespace http

#endif // EXECUTEDYNAMICRESOURCECONTROLLER_HPP