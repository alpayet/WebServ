/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResourceDtoMapper.hpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:06:28 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/27 05:24:54 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETESTATICRESOURCEDTOMAPPER_HPP
#define DELETESTATICRESOURCEDTOMAPPER_HPP

#include "application/use_cases/delete_static_resource/DeleteStaticResource.hpp"

namespace http {
class Request;
class RoutePolicy;

class DeleteStaticResourceDtoMapper
{
  public:
	static app::useCase::DeleteStaticResource::Input
	toDto(Request const &request, RoutePolicy const &routePolicy);

  private:
	DeleteStaticResourceDtoMapper(void);
};
} // namespace http

#endif // DELETESTATICRESOURCEDTOMAPPER_HPP