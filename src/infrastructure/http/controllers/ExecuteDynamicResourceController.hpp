/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourceController.hpp               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:46:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/01 02:17:31 by alpayet          ###   ########.fr       */
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
class Context;
struct RoutePolicy;
class ILimitsProvider;

class ExecuteDynamicResourceController
{
  public:
	ExecuteDynamicResourceController(
		app::useCase::ExecuteDynamicResource &useCase, ILimitsProvider &limitsProvider
	);

	void operator()(Context &context, RoutePolicy const &routePolicy);

  private:
	ExecuteDynamicResourceController(ExecuteDynamicResourceController const &src);
	ExecuteDynamicResourceController &operator=(ExecuteDynamicResourceController const &rhs);

	app::useCase::ExecuteDynamicResource &_useCase;
	ILimitsProvider						 &_limitsProvider;

	static std::map<std::string, std::string> createMetaVariables(Request const &request);
};
} // namespace http

#endif // EXECUTEDYNAMICRESOURCECONTROLLER_HPP