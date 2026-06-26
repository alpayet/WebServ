/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResource.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/26 04:01:36 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVESTATICRESOURCEUSECASE_HPP
#define SERVESTATICRESOURCEUSECASE_HPP

#include "application/ResourceStatus.hpp"
#include <string>
#include <vector>

namespace domain {
class ResourceMetaData;
} // namespace domain

namespace app {
class IResourceLocator;
class IResourceReader;
class IStaticResourceStorage;
class ICollectionExplorer;

namespace useCase {
class ServeStaticResource
{
  public:
	struct Input
	{
		Input(
			std::string const			   &id,
			std::string const			   &matchedRoute,
			std::string const			   &rootPath,
			bool const						isListingEnabled,
			std::vector<std::string> const &indexesId
		)
			: id(id), rootPath(rootPath), isListingEnabled(isListingEnabled), indexesId(indexesId)
		{}
		std::string				 id;
		std::string				 matchedRoute;
		std::string				 rootPath;
		bool					 isListingEnabled;
		std::vector<std::string> indexesId;
	};
	class IOutputPort
	{
	  public:
		virtual ~IOutputPort() {}

		virtual void presentContent(
			ResourceStatus const resourceStatus,
			std::size_t const	 resourceSize,
			IResourceReader		*resourceReader
		) = 0;
		virtual void presentListing(
			ResourceStatus const resourceStatus, std::vector<char> const &CollectionData
		) = 0;
	};

  public:
	ServeStaticResource(
		IResourceLocator	   &resourceLocator,
		IStaticResourceStorage &staticResourceStorage,
		ICollectionExplorer	   &collectionExplorer
	);

	void execute(Input const &dtoInput, IOutputPort &outputPort);

  private:
	ServeStaticResource(ServeStaticResource const &src);
	ServeStaticResource &operator=(ServeStaticResource const &rhs);

	void ServeStaticResource::serveContent(
		Input const &dtoInput, IOutputPort &outputPort, domain::ResourceMetaData const &metaData
	);
	void ServeStaticResource::generateListing(
		Input const &dtoInput, IOutputPort &outputPort, domain::ResourceMetaData const &metaData
	);

	IResourceLocator	   &_resourceLocator;
	IStaticResourceStorage &_staticResourceStorage;
	ICollectionExplorer	   &_collectionExplorer;
};
} // namespace useCase
} // namespace app

#endif // SERVESTATICRESOURCEUSECASE_HPP