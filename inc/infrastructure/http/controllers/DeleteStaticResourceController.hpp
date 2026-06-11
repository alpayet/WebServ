/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResourceController.hpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:46:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/11 15:26:14 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETESTATICRESOURCECONTROLLER_HPP
#define DELETESTATICRESOURCECONTROLLER_HPP

namespace useCase
{
	class DeleteStaticResource;
} // namespace useCase

struct RoutePolicy;

namespace http
{
	class Request;
	class Response;

	class DeleteStaticResourceController
	{
	  public:
		DeleteStaticResourceController(useCase::DeleteStaticResource &useCase);

		void DeleteStaticResourceController::operator()(
			Request const &request, Response &response, RoutePolicy const &routePolicy
		);

	  private:
		DeleteStaticResourceController(DeleteStaticResourceController const &src);
		DeleteStaticResourceController &operator=(DeleteStaticResourceController const &rhs);

		useCase::DeleteStaticResource &_useCase;
	};
} // namespace http

#endif // DELETESTATICRESOURCECONTROLLER_HPP