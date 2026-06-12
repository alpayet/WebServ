/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResourceDtoMapper.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:09:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:24:04 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/mappers/DeleteStaticResourceDtoMapper.hpp"
#include "application/use_cases/delete_static_resource/DeleteStaticResource.hpp"
#include "infrastructure/http/Request.hpp"

namespace http {
app::useCase::DeleteStaticResource::Input
DeleteStaticResourceDtoMapper::toDto(Request const &request, app::RoutePolicy const &routePolicy)
{
	(app::useCase::DeleteStaticResource::Input){.id = request.target, .routePolicy = routePolicy};
}
} // namespace http