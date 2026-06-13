/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResourceDtoMapper.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:09:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/13 01:44:12 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/mappers/DeleteStaticResourceDtoMapper.hpp"
#include "application/use_cases/delete_static_resource/DeleteStaticResource.hpp"
#include "infrastructure/http/Request.hpp"

namespace http {
app::useCase::DeleteStaticResource::Input
DeleteStaticResourceDtoMapper::toDto(Request const &request, app::RoutePolicy const &routePolicy)
{
	return ((app::useCase::DeleteStaticResource::Input){
		.id = request.target, .routePolicy = routePolicy
	});
}
} // namespace http