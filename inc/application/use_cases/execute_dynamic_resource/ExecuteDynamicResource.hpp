/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResource.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:08:10 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTEDYNAMICRESOURCEUSECASE_HPP
#define EXECUTEDYNAMICRESOURCEUSECASE_HPP

#include "application/ports/RoutePolicy.hpp"
#include <map>
#include <string>

namespace app {
class IDynamicResourceExecutor;
class IResourceLocator;

namespace useCase {
class ExecuteDynamicResource
{
  public:
	struct Input
	{
		std::string						   id;
		RoutePolicy						   routePolicy;
		std::map<std::string, std::string> metaVariables;
	};
	struct Output
	{};

  public:
	ExecuteDynamicResource(
		IResourceLocator &resourceLocator, IDynamicResourceExecutor &dynamicResourceExecutor
	);

	Output execute(Input const &dtoInput);

  private:
	ExecuteDynamicResource(ExecuteDynamicResource const &src);
	ExecuteDynamicResource &operator=(ExecuteDynamicResource const &rhs);

	IResourceLocator		 &_resourceLocator;
	IDynamicResourceExecutor &_dynamicResourceExecutor;
};
} // namespace useCase
} // namespace app

#endif // EXECUTEDYNAMICRESOURCEUSECASE_HPP