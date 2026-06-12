/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResourceDtoMapper.hpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:06:28 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:20:01 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FINDSTATICRESOURCEDTOMAPPER_HPP
#define FINDSTATICRESOURCEDTOMAPPER_HPP

#include "application/use_cases/find_static_resource/FindStaticResource.hpp"

namespace http {
struct Request;

class FindStaticResourceDtoMapper
{
  public:
	static app::useCase::FindStaticResource::Input
	toDto(Request const &request, app::RoutePolicy const &routePolicy);

  private:
	FindStaticResourceDtoMapper(void);
};
} // namespace http

#endif // FINDSTATICRESOURCEDTOMAPPER_HPP