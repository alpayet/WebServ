/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResource.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/16 23:35:34 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETESTATICRESOURCEUSECASE_HPP
#define DELETESTATICRESOURCEUSECASE_HPP

#include <string>

namespace app {
class IResourceLocator;
class IStaticResourceStorage;

namespace useCase {
class DeleteStaticResource
{
  public:
	struct Input
	{
		Input(std::string const &id, std::string const &rootPath) : id(id), rootPath(rootPath) {}
		std::string id;
		std::string rootPath;
	};
	class IOutputPort
	{
	  public:
		virtual ~IOutputPort() {}
	};

  public:
	DeleteStaticResource(
		IResourceLocator &resourceLocator, IStaticResourceStorage &staticResourceStorage
	);

	void execute(Input const &dtoInput, IOutputPort &outputPort);

  private:
	DeleteStaticResource(DeleteStaticResource const &src);
	DeleteStaticResource &operator=(DeleteStaticResource const &rhs);

	IResourceLocator	   &_resourceLocator;
	IStaticResourceStorage &_staticResourceStorage;
};
} // namespace useCase
} // namespace app

#endif // DELETESTATICRESOURCEUSECASE_HPP