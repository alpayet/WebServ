/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourcePresenter.hpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:45:29 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/16 23:19:07 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVESTATICRESOURCEPRESENTER_HPP
#define SERVESTATICRESOURCEPRESENTER_HPP

#include "application/use_cases/serve_static_resource/ServeStaticResource.hpp"
#include "infrastructure/http/messages/Response.hpp"
#include <vector>

namespace http {
class ServeStaticResourcePresenter : public app::useCase::ServeStaticResource::IOutputPort
{
  public:
	virtual ~ServeStaticResourcePresenter() {}

	Response const &getResponse(void) const;

	virtual void presentContent(app::IStaticResourceReader *resourceReader);

	virtual void presentListing(std::vector<char> CollectionData);

  private:
	Response _response;
};
} // namespace http

#endif // SERVESTATICRESOURCEPRESENTER_HPP