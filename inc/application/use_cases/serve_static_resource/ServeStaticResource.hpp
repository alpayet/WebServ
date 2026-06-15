/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResource.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/15 03:35:13 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVESTATICRESOURCEUSECASE_HPP
#define SERVESTATICRESOURCEUSECASE_HPP

#include <string>

namespace domain {
class ResourceMetaData;
} // namespace domain

namespace app {
class IResourceLocator;
class IStaticResourceStorage;
class IServeStaticResourcePresenter;

namespace useCase {
class ServeStaticResource
{
  public:
	struct Input
	{
		Input(
			std::string const			   &id,
			std::string const			   &rootPath,
			bool const						isListingEnabled,
			std::vector<std::string> const &indexesId
		)
			: id(id), rootPath(rootPath), isListingEnabled(isListingEnabled), indexesId(indexesId)
		{}
		std::string				 id;
		std::string				 rootPath;
		bool					 isListingEnabled;
		std::vector<std::string> indexesId;
	};

  public:
	ServeStaticResource(
		IResourceLocator			  &resourceLocator,
		IStaticResourceStorage		  &staticResourceStorage,
		IServeStaticResourcePresenter &serveStaticResourcePresenter
	);

	void execute(Input const &dtoInput);

  private:
	ServeStaticResource(ServeStaticResource const &src);
	ServeStaticResource &operator=(ServeStaticResource const &rhs);

	void ServeStaticResource::serveContent(
		Input const &dtoInput, domain::ResourceMetaData const &metaData
	);
	void ServeStaticResource::generateListing(
		Input const &dtoInput, domain::ResourceMetaData const &metaData
	);

	IResourceLocator			  &_resourceLocator;
	IStaticResourceStorage		  &_staticResourceStorage;
	IServeStaticResourcePresenter &_serveStaticResourcePresenter;
};
} // namespace useCase
} // namespace app

#endif // SERVESTATICRESOURCEUSECASE_HPP