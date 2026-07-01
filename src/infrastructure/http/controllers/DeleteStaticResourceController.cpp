/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResourceController.cpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:30:26 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/01 01:58:35 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/controllers/DeleteStaticResourceController.hpp"
#include "application/use_cases/delete_static_resource/DeleteStaticResource.hpp"
#include "infrastructure/http/Context.hpp"
#include "infrastructure/http/mappers/DeleteStaticResourceDtoMapper.hpp"
#include "infrastructure/http/presenters/DeleteStaticResourcePresenter.hpp"
#include "infrastructure/http/request/Request.hpp"

namespace http {
DeleteStaticResourceController::DeleteStaticResourceController(
	app::useCase::DeleteStaticResource &useCase
)
	: _useCase(useCase)
{}

void DeleteStaticResourceController::operator()(Context &context, RoutePolicy const &routePolicy)
{
	app::useCase::DeleteStaticResource::Input const &dto =
		DeleteStaticResourceDtoMapper::toDto(context.input.state.request, routePolicy);

	DeleteStaticResourcePresenter presenter;

	_useCase.execute(dto, presenter);

	DeleteStaticResourcePresenter::ViewModel const &viewModel = presenter.getViewModel();
	context.output.response = viewModel.response;
}
} // namespace http