/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResource.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/11 15:50:48 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FINDSTATICRESOURCEUSECASE_HPP
#define FINDSTATICRESOURCEUSECASE_HPP

#include "application/ports/RoutePolicy.hpp"
#include <string>

class IStaticResourceLocator;
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
			IStaticResourceLocator &staticResourceLocator,
			IStaticResourceStorage &staticResourceStorage
		);

		Output execute(Input const &dtoInput);

	  private:
		FindStaticResource(FindStaticResource const &src);
		FindStaticResource &operator=(FindStaticResource const &rhs);

		IStaticResourceLocator &_staticResourceLocator;
		IStaticResourceStorage &_staticResourceStorage;
	};
} // namespace useCase

#endif // FINDSTATICRESOURCEUSECASE_HPP