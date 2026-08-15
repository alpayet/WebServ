/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RoutePolicy.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 10:05:20 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:19:33 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTEPOLICY_HPP
#define ROUTEPOLICY_HPP

#include <string>
#include <vector>

namespace webserv {
namespace http {
struct RoutePolicy
{
	std::string				 matchedRoute;
	std::string				 rootPath;
	bool					 isListingEnabled;
	std::vector<std::string> indexesId;
	std::vector<std::string> allowedMethods;
	bool					 hasReturn;
	unsigned short			 returnCode;
	bool					 isCgi;
};
} // namespace http
} // namespace webserv

#endif // ROUTEPOLICY_HPP