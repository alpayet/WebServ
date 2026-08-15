/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResource.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:45:29 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:15:26 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVESTATICRESOURCEPRESENTER_HPP
#define SERVESTATICRESOURCEPRESENTER_HPP

#include "application/ResourceStatus.hpp"
#include "application/use_cases/serve_static_resource/ServeStaticResource.hpp"
#include "infrastructure/server/application_protocol/http/response/Response.hpp"
#include <string>
#include <vector>

namespace webserv {
namespace http {
namespace presenter {
class ServeStaticResource : public app::useCase::ServeStaticResource::IOutputPort
{
  public:
	struct ViewModel
	{
		ViewModel(void) : reader(NULL) {}

		Response			  response;
		app::IResourceReader *reader;
	};

  public:
	ServeStaticResource(void) {}
	virtual ~ServeStaticResource(void) {}

	ViewModel const &getViewModel(void) const;

	virtual void presentStaticContent(
		app::ResourceStatus status, std::size_t resourceSize, app::IResourceReader *resourceReader
	);
	virtual void presentListing(
		app::ResourceStatus						 status,
		std::string const						&id,
		std::vector<app::CollectionEntry> const &collectionData
	);

  private:
	ServeStaticResource(ServeStaticResource const &src);
	ServeStaticResource &operator=(ServeStaticResource const &rhs);

	ViewModel _viewModel;
};
} // namespace presenter
} // namespace http
} // namespace webserv

#endif // SERVESTATICRESOURCEPRESENTER_HPP