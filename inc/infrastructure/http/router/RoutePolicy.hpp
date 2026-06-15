/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RoutePolicy.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 10:05:20 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/15 01:54:07 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTEPOLICY_HPP
#define ROUTEPOLICY_HPP

#include <string>
#include <vector>
namespace http {
struct RoutePolicy
{
	std::string				 rootPath;
	bool					 isListingEnabled;
	std::vector<std::string> indexesId;
	std::vector<std::string> allowedMethods;
};
} // namespace http

#endif // ROUTEPOLICY_HPP