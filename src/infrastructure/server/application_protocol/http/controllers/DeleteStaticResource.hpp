/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResourceController.hpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:46:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/09 21:57:12 by alpayet          ###   ########.fr       */
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

namespace controller
{
	class DeleteStaticResource
	{
	  public:
		DeleteStaticResource(app::useCase::DeleteStaticResource &useCase);

		void operator()(Context &context, RoutePolicy const &routePolicy);

	  private:
		DeleteStaticResource(DeleteStaticResource const &src);
		DeleteStaticResource &operator=(DeleteStaticResource const &rhs);

		app::useCase::DeleteStaticResource &_useCase;
	};
} // namespace controller

} // namespace http


#endif // DELETESTATICRESOURCECONTROLLER_HPP