/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResourceDtoMapper.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:09:06 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/11 15:51:40 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/mappers/DeleteStaticResourceDtoMapper.hpp"
#include "application/use_cases/delete_static_resource/DeleteStaticResource.hpp"
#include "infrastructure/http/Request.hpp"

namespace http
{
	useCase::DeleteStaticResource::Input
	DeleteStaticResourceDtoMapper::toDto(Request const &request, RoutePolicy const &routePolicy)
	{
		(useCase::DeleteStaticResource::Input){.id = request.target, .routePolicy = routePolicy};
	}
} // namespace http