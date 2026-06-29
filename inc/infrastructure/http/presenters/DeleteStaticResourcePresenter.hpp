/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResourcePresenter.hpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:45:12 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/29 21:12:06 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETESTATICRESOURCEPRESENTER_HPP
#define DELETESTATICRESOURCEPRESENTER_HPP

#include "application/ResourceStatus.hpp"
#include "application/use_cases/delete_static_resource/DeleteStaticResource.hpp"
#include "infrastructure/http/response/Response.hpp"
#include <string>
#include <vector>

namespace http {

class DeleteStaticResourcePresenter : public app::useCase::DeleteStaticResource::IOutputPort
{
  public:
	struct ViewModel
	{
		Response response;
	};

  public:
	DeleteStaticResourcePresenter(void) {}
	virtual ~DeleteStaticResourcePresenter(void) {}

	ViewModel const &getViewModel(void) const;

	virtual void presentDeletedResource(app::ResourceStatus const status);

  private:
	DeleteStaticResourcePresenter(DeleteStaticResourcePresenter const &src);
	DeleteStaticResourcePresenter &operator=(DeleteStaticResourcePresenter const &rhs);

	ViewModel _viewModel;
};
} // namespace http

#endif // DELETESTATICRESOURCEPRESENTER_HPP