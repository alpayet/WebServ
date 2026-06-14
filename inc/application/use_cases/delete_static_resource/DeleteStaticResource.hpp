/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResource.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/14 21:48:48 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETESTATICRESOURCEUSECASE_HPP
#define DELETESTATICRESOURCEUSECASE_HPP

#include "application/ports/RoutePolicy.hpp"
#include <string>

namespace app {
class IResourceLocator;
class IStaticResourceStorage;
class IDeleteStaticResourcePresenter;

namespace useCase {
class DeleteStaticResource
{
  public:
	struct Input
	{
		std::string id;
		RoutePolicy routePolicy;
	};
	struct Output
	{};

  public:
	DeleteStaticResource(
		IResourceLocator			   &resourceLocator,
		IStaticResourceStorage		   &staticResourceStorage,
		IDeleteStaticResourcePresenter &deleteStaticResourcePresenter
	);

	Output execute(Input const &dtoInput);

  private:
	DeleteStaticResource(DeleteStaticResource const &src);
	DeleteStaticResource &operator=(DeleteStaticResource const &rhs);

	IResourceLocator			   &_resourceLocator;
	IStaticResourceStorage		   &_staticResourceStorage;
	IDeleteStaticResourcePresenter &_deleteStaticResourcePresenter;
};
} // namespace useCase
} // namespace app

#endif // DELETESTATICRESOURCEUSECASE_HPP