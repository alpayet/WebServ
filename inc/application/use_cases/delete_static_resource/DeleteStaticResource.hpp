/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResource.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/11 15:50:15 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETESTATICRESOURCEUSECASE_HPP
#define DELETESTATICRESOURCEUSECASE_HPP

#include "application/ports/RoutePolicy.hpp"
#include <string>

class IStaticResourceLocator;
class IStaticResourceStorage;
struct RoutePolicy;

namespace useCase
{
	class DeleteStaticResource
	{
	  public:
		struct Input
		{
			std::string id;
			RoutePolicy routePolicy;
		};
		struct Output
		{
		};

	  public:
		DeleteStaticResource(
			IStaticResourceLocator &staticResourceLocator,
			IStaticResourceStorage &staticResourceStorage
		);

		Output execute(Input const &dtoInput);

	  private:
		DeleteStaticResource(DeleteStaticResource const &src);
		DeleteStaticResource &operator=(DeleteStaticResource const &rhs);

		IStaticResourceLocator &_staticResourceLocator;
		IStaticResourceStorage &_staticResourceStorage;
	};
} // namespace useCase

#endif // DELETESTATICRESOURCEUSECASE_HPP