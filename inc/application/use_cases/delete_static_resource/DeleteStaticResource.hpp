/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResource.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/15 03:35:41 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETESTATICRESOURCEUSECASE_HPP
#define DELETESTATICRESOURCEUSECASE_HPP

#include <string>

namespace app {
class IResourceLocator;
class IStaticResourceStorage;
class IDeleteStaticResourcePresenter;

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
	struct Output
	{};

  public:
	DeleteStaticResource(
		IResourceLocator			   &resourceLocator,
		IStaticResourceStorage		   &staticResourceStorage,
		IDeleteStaticResourcePresenter &deleteStaticResourcePresenter
	);

	Output execute(Input const &dtoInput);

  private:
	DeleteStaticResource(DeleteStaticResource const &src);
	DeleteStaticResource &operator=(DeleteStaticResource const &rhs);

	IResourceLocator			   &_resourceLocator;
	IStaticResourceStorage		   &_staticResourceStorage;
	IDeleteStaticResourcePresenter &_deleteStaticResourcePresenter;
};
} // namespace useCase
} // namespace app

#endif // DELETESTATICRESOURCEUSECASE_HPP