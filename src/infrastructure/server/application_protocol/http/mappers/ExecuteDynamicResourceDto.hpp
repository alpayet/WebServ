/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceDto.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:06:28 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:13:24 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTEDYNAMICRESOURCEDTOMAPPER_HPP
#define EXECUTEDYNAMICRESOURCEDTOMAPPER_HPP

#include "application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.hpp"

namespace webserv {
namespace http {
class Request;
struct RoutePolicy;

namespace mapper {
class ExecuteDynamicResourceDto
{
  public:
	static app::useCase::ExecuteDynamicResource::Input toDto(
		Request const							 &request,
		RoutePolicy const						 &routePolicy,
		std::string const						 &bodyPath,
		std::map<std::string, std::string> const &metaVariables
	);

  private:
	ExecuteDynamicResourceDto(void);
};
} // namespace mapper
} // namespace http
} // namespace webserv

#endif // EXECUTEDYNAMICRESOURCEDTOMAPPER_HPP