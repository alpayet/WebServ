/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResource.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/09 04:01:31 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTEDYNAMICRESOURCEUSECASE_HPP
#define EXECUTEDYNAMICRESOURCEUSECASE_HPP

#include "application/ResourceStatus.hpp"
#include <map>
#include <string>

namespace app {
class IResourceLocator;
class IDynamicResourceExecutor;

namespace useCase {
class ExecuteDynamicResource
{
  public:
	struct Input
	{
		Input(
			std::string const						 &id,
			std::string const						 &matchedRoute,
			std::string const						 &rootPath,
			std::string const						 &bodyPath,
			std::map<std::string, std::string> const &metaVariables
		)
			: id(id), matchedRoute(matchedRoute), rootPath(rootPath), bodyPath(bodyPath),
			  metaVariables(metaVariables)
		{}
		std::string						   id;
		std::string						   matchedRoute;
		std::string						   rootPath;
		std::string						   bodyPath;
		std::map<std::string, std::string> metaVariables;
	};

  public:
	ExecuteDynamicResource(
		IResourceLocator &resourceLocator, IDynamicResourceExecutor &dynamicResourceExecutor
	);

	void execute(Input const &dtoInput);

  private:
	ExecuteDynamicResource(ExecuteDynamicResource const &src);
	ExecuteDynamicResource &operator=(ExecuteDynamicResource const &rhs);

	IResourceLocator		 &_resourceLocator;
	IDynamicResourceExecutor &_dynamicResourceExecutor;
};
} // namespace useCase
} // namespace app

#endif // EXECUTEDYNAMICRESOURCEUSECASE_HPP