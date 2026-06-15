/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResource.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/15 03:55:04 by alpayet          ###   ########.fr       */
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
			std::size_t const						  bodySize,
			std::size_t const						  maxBodySize,
			std::map<std::string, std::string> const &metaVariables
		)
			: id(id), rootPath(rootPath), bodyPath(bodyPath), bodySize(bodySize),
			  maxBodySize(maxBodySize), metaVariables(metaVariables)
		{}
		std::string						   id;
		std::string						   rootPath;
		std::string						   bodyPath;
		std::size_t						   bodySize;
		std::size_t						   maxBodySize;
		std::map<std::string, std::string> metaVariables;
	};
	struct Output
	{};

  public:
	ExecuteDynamicResource(
		IResourceLocator				 &resourceLocator,
		IDynamicResourceExecutor		 &dynamicResourceExecutor,
		IExecuteDynamicResourcePresenter &executeDynamicResourcePresenter
	);

	Output execute(Input const &dtoInput);

  private:
	ExecuteDynamicResource(ExecuteDynamicResource const &src);
	ExecuteDynamicResource &operator=(ExecuteDynamicResource const &rhs);

	IResourceLocator				 &_resourceLocator;
	IDynamicResourceExecutor		 &_dynamicResourceExecutor;
	IExecuteDynamicResourcePresenter &_executeDynamicResourcePresenter;
};
} // namespace useCase
} // namespace app

#endif // EXECUTEDYNAMICRESOURCEUSECASE_HPP