/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourceDto.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:06:28 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/09 22:23:53 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVESTATICRESOURCEDTOMAPPER_HPP
#define SERVESTATICRESOURCEDTOMAPPER_HPP

#include "application/use_cases/serve_static_resource/ServeStaticResource.hpp"

namespace http {
class Request;
struct RoutePolicy;

namespace mapper {
class ServeStaticResourceDto
{
  public:
	static app::useCase::ServeStaticResource::Input
	toDto(Request const &request, RoutePolicy const &routePolicy);

  private:
	ServeStaticResourceDto(void);
};
} // namespace mapper

} // namespace http

#endif // SERVESTATICRESOURCEDTOMAPPER_HPP