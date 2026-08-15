/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResource.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:38:12 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTEDYNAMICRESOURCEUSECASE_HPP
#define EXECUTEDYNAMICRESOURCEUSECASE_HPP

#include "application/ResourceStatus.hpp"
#include <map>
#include <string>

namespace webserv {
namespace app {
class IResourceLocator;
class IDynamicResourceExecutor;
struct StreamInfo;

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

	class IOutputPort
	{
	  public:
		virtual ~IOutputPort() {}

		virtual void presentStream(StreamInfo stream_info) = 0;
	};

  public:
	ExecuteDynamicResource(
		IResourceLocator const &resourceLocator, IDynamicResourceExecutor &dynamicResourceExecutor
	);

	void execute(Input const &dtoInput, IOutputPort &outputPort);

  private:
	ExecuteDynamicResource(ExecuteDynamicResource const &src);
	ExecuteDynamicResource &operator=(ExecuteDynamicResource const &rhs);

	IResourceLocator const	 &_resourceLocator;
	IDynamicResourceExecutor &_dynamicResourceExecutor;
};
} // namespace useCase
} // namespace app
} // namespace webserv

#endif // EXECUTEDYNAMICRESOURCEUSECASE_HPP