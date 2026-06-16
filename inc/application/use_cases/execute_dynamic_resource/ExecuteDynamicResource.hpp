/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResource.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/16 23:34:51 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTEDYNAMICRESOURCEUSECASE_HPP
#define EXECUTEDYNAMICRESOURCEUSECASE_HPP

#include <map>
#include <string>

namespace app {
class IDynamicResourceExecutor;
class IResourceLocator;
class IExecuteDynamicResourcePresenter;

namespace useCase {
class ExecuteDynamicResource
{
  public:
	struct Input
	{
		Input(
			std::string const						 &id,
			std::string const						 &rootPath,
			std::string const						 &bodyPath,
			std::map<std::string, std::string> const &metaVariables
		)
			: id(id), rootPath(rootPath), bodyPath(bodyPath), metaVariables(metaVariables)
		{}
		std::string						   id;
		std::string						   rootPath;
		std::string						   bodyPath;
		std::map<std::string, std::string> metaVariables;
	};
	class IOutputPort
	{
	  public:
		virtual ~IOutputPort() {}
	};

  public:
	ExecuteDynamicResource(
		IResourceLocator &resourceLocator, IDynamicResourceExecutor &dynamicResourceExecutor
	);

	void execute(Input const &dtoInput, IOutputPort &outputPort);

  private:
	ExecuteDynamicResource(ExecuteDynamicResource const &src);
	ExecuteDynamicResource &operator=(ExecuteDynamicResource const &rhs);

	IResourceLocator		 &_resourceLocator;
	IDynamicResourceExecutor &_dynamicResourceExecutor;
};
} // namespace useCase
} // namespace app

#endif // EXECUTEDYNAMICRESOURCEUSECASE_HPP