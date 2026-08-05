/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourcePresenter.hpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:45:29 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/04 19:55:52 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVESTATICRESOURCEPRESENTER_HPP
#define SERVESTATICRESOURCEPRESENTER_HPP

#include "application/ResourceStatus.hpp"
#include "application/use_cases/serve_static_resource/ServeStaticResource.hpp"
#include "infrastructure/server/application_protocol/http/response/Response.hpp"
#include <string>
#include <vector>

namespace http {

class ServeStaticResourcePresenter : public app::useCase::ServeStaticResource::IOutputPort
{
  public:
	struct ViewModel
	{
		ViewModel(void) : reader(NULL) {}

		Response			  response;
		app::IResourceReader *reader;
	};

  public:
	ServeStaticResourcePresenter(void) {}
	virtual ~ServeStaticResourcePresenter(void) {}

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
	ServeStaticResourcePresenter(ServeStaticResourcePresenter const &src);
	ServeStaticResourcePresenter &operator=(ServeStaticResourcePresenter const &rhs);

	ViewModel _viewModel;
};
} // namespace http

#endif // SERVESTATICRESOURCEPRESENTER_HPP