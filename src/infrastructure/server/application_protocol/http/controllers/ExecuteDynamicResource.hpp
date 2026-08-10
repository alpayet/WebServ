/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResource.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:46:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/09 22:00:19 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTEDYNAMICRESOURCECONTROLLER_HPP
#define EXECUTEDYNAMICRESOURCECONTROLLER_HPP

#include <map>
#include <string>

namespace app {
namespace useCase {
class ExecuteDynamicResource;
} // namespace useCase
} // namespace app

namespace http {
class Request;
struct Context;
struct RoutePolicy;
class ILimitsProvider;

namespace controller {
class ExecuteDynamicResource
{
  public:
	ExecuteDynamicResource(
		app::useCase::ExecuteDynamicResource &useCase, ILimitsProvider const &limitsProvider
	);

	void operator()(Context &context, RoutePolicy const &routePolicy);

  private:
	ExecuteDynamicResource(ExecuteDynamicResource const &src);
	ExecuteDynamicResource &operator=(ExecuteDynamicResource const &rhs);

	app::useCase::ExecuteDynamicResource &_useCase;
	ILimitsProvider const				 &_limitsProvider;

	static std::map<std::string, std::string> createMetaVariables(Request const &request);
};
} // namespace controller

} // namespace http

#endif // EXECUTEDYNAMICRESOURCECONTROLLER_HPP