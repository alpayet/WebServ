/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourcePresenter.hpp                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:45:21 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/01 01:48:15 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTEDYNAMICRESOURCEPRESENTER_HPP
#define EXECUTEDYNAMICRESOURCEPRESENTER_HPP

#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.hpp"
#include "infrastructure/http/response/Response.hpp"
#include <string>
#include <vector>

namespace http {

class ExecuteDynamicResourcePresenter : public app::useCase::ExecuteDynamicResource::IOutputPort
{
  public:
	struct ViewModel
	{
		ViewModel(void) : reader(NULL) {}

		Response			  response;
		app::IResourceReader *reader;
	};

  public:
	ExecuteDynamicResourcePresenter(void) {}
	virtual ~ExecuteDynamicResourcePresenter(void) {}

	ViewModel const &getViewModel(void) const;

	virtual void presentDynamicContent(app::IResourceReader *resourceReader);

  private:
	ExecuteDynamicResourcePresenter(ExecuteDynamicResourcePresenter const &src);
	ExecuteDynamicResourcePresenter &operator=(ExecuteDynamicResourcePresenter const &rhs);

	ViewModel _viewModel;
};
} // namespace http

#endif // EXECUTEDYNAMICRESOURCEPRESENTER_HPP