/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourcePresenter.hpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:45:29 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/17 04:14:15 by alpayet          ###   ########.fr       */
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
	virtual ~ServeStaticResourcePresenter() {}

	Response const &getResponse(void) const;

	virtual void
	presentContent(app::ResourceStatus status, app::IResourceReader *resourceReader) = 0;
	virtual void presentListing(app::ResourceStatus status, std::vector<char> CollectionData) = 0;

  private:
	Response _response;
};
} // namespace http

#endif // SERVESTATICRESOURCEPRESENTER_HPP