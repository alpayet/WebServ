/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceDtoMapper.cpp                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:09:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:24:09 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/mappers/ExecuteDynamicResourceDtoMapper.hpp"
#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.hpp"
#include "infrastructure/http/Request.hpp"

namespace http {
app::useCase::ExecuteDynamicResource::Input
ExecuteDynamicResourceDtoMapper::toDto(Request const &request, app::RoutePolicy const &routePolicy)
{
	(app::useCase::ExecuteDynamicResource::Input){.id = request.target, .routePolicy = routePolicy};
}
} // namespace http