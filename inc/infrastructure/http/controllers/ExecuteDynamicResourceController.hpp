/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceController.hpp               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:46:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/15 03:12:41 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTEDYNAMICRESOURCECONTROLLER_HPP
#define EXECUTEDYNAMICRESOURCECONTROLLER_HPP

namespace app {
namespace useCase {
class ExecuteDynamicResource;
} // namespace useCase
} // namespace app

namespace http {
class Request;
class Response;
class ILimitsProvider;

class ExecuteDynamicResourceController
{
  public:
	ExecuteDynamicResourceController(
		app::useCase::ExecuteDynamicResource &useCase, ILimitsProvider &limitsProvider
	);

	void ExecuteDynamicResourceController::operator()(
		Request const &request, Response &response, RoutePolicy const &routePolicy
	);

  private:
	ExecuteDynamicResourceController(ExecuteDynamicResourceController const &src);
	ExecuteDynamicResourceController &operator=(ExecuteDynamicResourceController const &rhs);

	app::useCase::ExecuteDynamicResource &_useCase;
	ILimitsProvider						 &_limitsProvider;
};
} // namespace http

#endif // EXECUTEDYNAMICRESOURCECONTROLLER_HPP