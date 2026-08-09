/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResourceDto.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:06:28 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/09 22:23:05 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETESTATICRESOURCEDTOMAPPER_HPP
#define DELETESTATICRESOURCEDTOMAPPER_HPP

#include "application/use_cases/delete_static_resource/DeleteStaticResource.hpp"

namespace http {
class Request;
struct RoutePolicy;

namespace mapper {
class DeleteStaticResourceDto
{
  public:
	static app::useCase::DeleteStaticResource::Input
	toDto(Request const &request, RoutePolicy const &routePolicy);

  private:
	DeleteStaticResourceDto(void);
};
} // namespace mapper

} // namespace http

#endif // DELETESTATICRESOURCEDTOMAPPER_HPP