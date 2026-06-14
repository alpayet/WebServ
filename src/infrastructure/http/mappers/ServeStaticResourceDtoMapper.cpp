/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourceDtoMapper.cpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:09:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/14 21:46:11 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/mappers/ServeStaticResourceDtoMapper.hpp"
#include "application/use_cases/serve_static_resource/ServeStaticResource.hpp"
#include "infrastructure/http/Request.hpp"

namespace http {
app::useCase::ServeStaticResource::Input
ServeStaticResourceDtoMapper::toDto(Request const &request, app::RoutePolicy const &routePolicy)
{
	return (
		(app::useCase::ServeStaticResource::Input){.id = request.target, .routePolicy = routePolicy}
	);
}
} // namespace http