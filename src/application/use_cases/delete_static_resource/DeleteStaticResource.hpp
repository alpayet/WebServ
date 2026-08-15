/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResource.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:37:56 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETESTATICRESOURCEUSECASE_HPP
#define DELETESTATICRESOURCEUSECASE_HPP

#include "application/ResourceStatus.hpp"
#include <string>

namespace webserv {
namespace app {
class IResourceLocator;
class IStaticResourceStorage;

namespace useCase {
class DeleteStaticResource
{
  public:
	struct Input
	{
		Input(std::string const &id, std::string const &matchedRoute, std::string const &rootPath)
			: id(id), matchedRoute(matchedRoute), rootPath(rootPath)
		{}

		std::string id;
		std::string matchedRoute;
		std::string rootPath;
	};

	class IOutputPort
	{
	  public:
		virtual ~IOutputPort() {}

		virtual void presentDeletedResource(ResourceStatus const resourceStatus) = 0;
	};

  public:
	DeleteStaticResource(
		IResourceLocator const &resourceLocator, IStaticResourceStorage &staticResourceStorage
	);

	void execute(Input const &dtoInput, IOutputPort &outputPort);

  private:
	DeleteStaticResource(DeleteStaticResource const &src);
	DeleteStaticResource &operator=(DeleteStaticResource const &rhs);

	IResourceLocator const &_resourceLocator;
	IStaticResourceStorage &_staticResourceStorage;
};
} // namespace useCase
} // namespace app
} // namespace webserv

#endif // DELETESTATICRESOURCEUSECASE_HPP