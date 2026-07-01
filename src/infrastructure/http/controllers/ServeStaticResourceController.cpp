/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourceController.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:30:26 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/01 01:58:32 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/controllers/ServeStaticResourceController.hpp"
#include "application/use_cases/serve_static_resource/ServeStaticResource.hpp"
#include "infrastructure/http/Context.hpp"
#include "infrastructure/http/mappers/ServeStaticResourceDtoMapper.hpp"
#include "infrastructure/http/presenters/ServeStaticResourcePresenter.hpp"
#include "infrastructure/http/request/Request.hpp"

namespace http {
ServeStaticResourceController::ServeStaticResourceController(
	app::useCase::ServeStaticResource &useCase
)
	: _useCase(useCase)
{}

void ServeStaticResourceController::operator()(Context &context, RoutePolicy const &routePolicy)
{
	app::useCase::ServeStaticResource::Input const &dto =
		ServeStaticResourceDtoMapper::toDto(context.input.state.request, routePolicy);

	ServeStaticResourcePresenter presenter;

	_useCase.execute(dto, presenter);

	ServeStaticResourcePresenter::ViewModel const &viewModel = presenter.getViewModel();
	context.output.response = viewModel.response;
	context.output.reader = viewModel.reader;
}
} // namespace http