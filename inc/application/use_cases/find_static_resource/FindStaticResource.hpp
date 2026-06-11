/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResource.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/11 19:51:12 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FINDSTATICRESOURCEUSECASE_HPP
#define FINDSTATICRESOURCEUSECASE_HPP

#include "application/ports/RoutePolicy.hpp"
#include <string>

class IResourceLocator;
class IStaticResourceStorage;

class IStaticResourceReader;

namespace useCase
{
	class FindStaticResource
	{
	  public:
		struct Input
		{
			std::string id;
			RoutePolicy routePolicy;
		};
		struct Output
		{
			IStaticResourceReader *resourceReader;
		};

	  public:
		FindStaticResource(
			IResourceLocator &resourceLocator, IStaticResourceStorage &staticResourceStorage
		);

		Output execute(Input const &dtoInput);

	  private:
		FindStaticResource(FindStaticResource const &src);
		FindStaticResource &operator=(FindStaticResource const &rhs);

		IResourceLocator	   &_resourceLocator;
		IStaticResourceStorage &_staticResourceStorage;
	};
} // namespace useCase

#endif // FINDSTATICRESOURCEUSECASE_HPP