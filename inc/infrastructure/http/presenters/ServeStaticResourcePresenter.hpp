/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourcePresenter.hpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:45:29 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/18 00:52:46 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVESTATICRESOURCEPRESENTER_HPP
#define SERVESTATICRESOURCEPRESENTER_HPP

#include "application/ResourceStatus.hpp"
#include "application/use_cases/serve_static_resource/ServeStaticResource.hpp"
#include "infrastructure/http/messages/Response.hpp"
#include <vector>

namespace http {

class ServeStaticResourcePresenter : public app::useCase::ServeStaticResource::IOutputPort
{
  public:
	struct ViewModel
	{
		app::IResourceReader *reader;
		Response			  response;
	};

  public:
	virtual ~ServeStaticResourcePresenter() {}

	ViewModel const &getViewModel(void) const;

	virtual void presentContent(
		app::ResourceStatus const	resourceStatus,
		std::size_t const			resourceSize,
		app::IResourceReader const *resourceReader
	) = 0;
	virtual void presentListing(
		app::ResourceStatus const resourceStatus, std::vector<char> const &CollectionData
	) = 0;

  private:
	ViewModel _viewModel;
};
} // namespace http

#endif // SERVESTATICRESOURCEPRESENTER_HPP