/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResource.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/11 19:51:12 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETESTATICRESOURCEUSECASE_HPP
#define DELETESTATICRESOURCEUSECASE_HPP

#include "application/ports/RoutePolicy.hpp"
#include <string>

class IResourceLocator;
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
			IResourceLocator &resourceLocator, IStaticResourceStorage &staticResourceStorage
		);

		Output execute(Input const &dtoInput);

	  private:
		DeleteStaticResource(DeleteStaticResource const &src);
		DeleteStaticResource &operator=(DeleteStaticResource const &rhs);

		IResourceLocator	   &_resourceLocator;
		IStaticResourceStorage &_staticResourceStorage;
	};
} // namespace useCase

#endif // DELETESTATICRESOURCEUSECASE_HPP