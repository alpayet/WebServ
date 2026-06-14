/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourceDtoMapper.hpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:06:28 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/14 21:46:42 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVESTATICRESOURCEDTOMAPPER_HPP
#define SERVESTATICRESOURCEDTOMAPPER_HPP

#include "application/use_cases/serve_static_resource/ServeStaticResource.hpp"

namespace http {
struct Request;

class ServeStaticResourceDtoMapper
{
  public:
	static app::useCase::ServeStaticResource::Input
	toDto(Request const &request, app::RoutePolicy const &routePolicy);

  private:
	ServeStaticResourceDtoMapper(void);
};
} // namespace http

#endif // SERVESTATICRESOURCEDTOMAPPER_HPP