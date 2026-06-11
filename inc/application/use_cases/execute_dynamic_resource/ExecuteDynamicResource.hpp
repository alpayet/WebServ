/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResource.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/11 19:52:21 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTEDYNAMICRESOURCEUSECASE_HPP
#define EXECUTEDYNAMICRESOURCEUSECASE_HPP

#include "application/ports/RoutePolicy.hpp"
#include <map>
#include <string>

class IDynamicResourceExecutor;
class IResourceLocator;

namespace useCase
{
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
		{
		};

	  public:
		ExecuteDynamicResource(
			IDynamicResourceExecutor &dynamicResourceExecutor, IResourceLocator &resourceLocator
		);

		Output execute(Input const &dtoInput);

	  private:
		ExecuteDynamicResource(ExecuteDynamicResource const &src);
		ExecuteDynamicResource &operator=(ExecuteDynamicResource const &rhs);

		IResourceLocator		 &_resourceLocator;
		IDynamicResourceExecutor &_dynamicResourceExecutor;
	};
} // namespace useCase

#endif // EXECUTEDYNAMICRESOURCEUSECASE_HPP