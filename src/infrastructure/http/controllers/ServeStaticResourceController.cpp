/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourceController.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:30:26 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/18 20:15:08 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/controllers/ServeStaticResourceController.hpp"
#include "application/use_cases/serve_static_resource/ServeStaticResource.hpp"
#include "infrastructure/http/Context.hpp"
#include "infrastructure/http/IVersionProvider.hpp"
#include "infrastructure/http/mappers/ServeStaticResourceDtoMapper.hpp"
#include "infrastructure/http/messages/Request.hpp"
#include "infrastructure/http/presenters/ServeStaticResourcePresenter.hpp"

namespace http {
ServeStaticResourceController::ServeStaticResourceController(
	app::useCase::ServeStaticResource &useCase, IVersionProvider &versionProvider
)

	: _useCase(useCase), _versionProvider(versionProvider)
{}

void ServeStaticResourceController::operator()(
	Request const &request, Context &context, RoutePolicy const &routePolicy
)
{
	app::useCase::ServeStaticResource::Input const &dto =
		ServeStaticResourceDtoMapper::toDto(request, routePolicy);

	ServeStaticResourcePresenter presenter(_versionProvider.getHttpVersion());
	_useCase.execute(dto, presenter);
}
} // namespace http