/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourcePresenter.hpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:45:29 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/22 21:40:36 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVESTATICRESOURCEPRESENTER_HPP
#define SERVESTATICRESOURCEPRESENTER_HPP

#include "application/ResourceStatus.hpp"
#include "application/use_cases/serve_static_resource/ServeStaticResource.hpp"
#include <string>
#include <vector>

namespace http {

class ServeStaticResourcePresenter : public app::useCase::ServeStaticResource::IOutputPort
{
  public:
	struct ViewModel
	{
		std::vector<char>	  rawHeaderBlock;
		app::IResourceReader *reader;
	};

  public:
	ServeStaticResourcePresenter(std::string const &httpVersion);
	virtual ~ServeStaticResourcePresenter(void) {}

	ViewModel const &getViewModel(void) const;

	virtual void presentContent(
		app::ResourceStatus const resourceStatus,
		std::size_t const		  resourceSize,
		app::IResourceReader	 *resourceReader
	);
	virtual void presentListing(
		app::ResourceStatus const resourceStatus, std::vector<char> const &CollectionData
	);

  private:
	ServeStaticResourcePresenter(ServeStaticResourcePresenter const &src);
	ServeStaticResourcePresenter &operator=(ServeStaticResourcePresenter const &rhs);

	ViewModel	_viewModel;
	std::string _httpVersion;
};
} // namespace http

#endif // SERVESTATICRESOURCEPRESENTER_HPP