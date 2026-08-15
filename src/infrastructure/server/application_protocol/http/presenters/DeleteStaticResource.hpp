/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResource.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:45:12 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:13:51 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETESTATICRESOURCEPRESENTER_HPP
#define DELETESTATICRESOURCEPRESENTER_HPP

#include "application/ResourceStatus.hpp"
#include "application/use_cases/delete_static_resource/DeleteStaticResource.hpp"
#include "infrastructure/server/application_protocol/http/response/Response.hpp"
#include <string>
#include <vector>

namespace webserv {
namespace http {
namespace presenter {
class DeleteStaticResource : public app::useCase::DeleteStaticResource::IOutputPort
{
  public:
	struct ViewModel
	{
		Response response;
	};

  public:
	DeleteStaticResource(void) {}
	virtual ~DeleteStaticResource(void) {}

	ViewModel const &getViewModel(void) const;

	virtual void presentDeletedResource(app::ResourceStatus status);

  private:
	DeleteStaticResource(DeleteStaticResource const &src);
	DeleteStaticResource &operator=(DeleteStaticResource const &rhs);

	ViewModel _viewModel;
};
} // namespace presenter
}
} // namespace http

#endif // DELETESTATICRESOURCEPRESENTER_HPP