/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResource.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/13 23:22:12 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FINDSTATICRESOURCEUSECASE_HPP
#define FINDSTATICRESOURCEUSECASE_HPP

#include "application/ports/RoutePolicy.hpp"
#include <string>

namespace app {
class IResourceLocator;
class IStaticResourceStorage;
class IStaticResourcePresenter;

namespace useCase {
class FindStaticResource
{
  public:
	struct Input
	{
		std::string id;
		RoutePolicy routePolicy;
	};

  public:
	FindStaticResource(
		IResourceLocator		 &resourceLocator,
		IStaticResourceStorage	 &staticResourceStorage,
		IStaticResourcePresenter &staticResourcePresenter
	);

	void execute(Input const &dtoInput);

  private:
	FindStaticResource(FindStaticResource const &src);
	FindStaticResource &operator=(FindStaticResource const &rhs);

	IResourceLocator		 &_resourceLocator;
	IStaticResourceStorage	 &_staticResourceStorage;
	IStaticResourcePresenter &_staticResourcePresenter;
};
} // namespace useCase
} // namespace app

#endif // FINDSTATICRESOURCEUSECASE_HPP