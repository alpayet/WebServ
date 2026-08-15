/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResource.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:47:47 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:38:36 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVESTATICRESOURCEUSECASE_HPP
#define SERVESTATICRESOURCEUSECASE_HPP

#include "application/ResourceStatus.hpp"
#include <string>
#include <vector>

namespace webserv {
namespace domain {
class ResourceMetaData;
} // namespace domain

namespace app {
class IResourceLocator;
class IStaticResourceStorage;
class IResourceReader;
class ICollectionExplorer;
struct CollectionEntry;

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
			: id(id), matchedRoute(matchedRoute), rootPath(rootPath),
			  isListingEnabled(isListingEnabled), indexesId(indexesId)
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

		virtual void presentStaticContent(
			ResourceStatus const status,
			std::size_t const	 resourceSize,
			IResourceReader		*resourceReader
		) = 0;
		virtual void presentListing(
			ResourceStatus const				status,
			std::string const				   &id,
			std::vector<CollectionEntry> const &collectionData
		) = 0;
	};

  public:
	ServeStaticResource(
		IResourceLocator const &resourceLocator,
		IStaticResourceStorage &staticResourceStorage,
		ICollectionExplorer	   &collectionExplorer
	);

	void execute(Input const &dtoInput, IOutputPort &outputPort);

  private:
	ServeStaticResource(ServeStaticResource const &src);
	ServeStaticResource &operator=(ServeStaticResource const &rhs);

	void serveContent(
		Input const &dtoInput, IOutputPort &outputPort, domain::ResourceMetaData const &metaData
	);
	void generateListing(
		Input const &dtoInput, IOutputPort &outputPort, domain::ResourceMetaData const &metaData
	);

	IResourceLocator const &_resourceLocator;
	IStaticResourceStorage &_staticResourceStorage;
	ICollectionExplorer	   &_collectionExplorer;
};
} // namespace useCase
} // namespace app
} // namespace webserv

#endif // SERVESTATICRESOURCEUSECASE_HPP