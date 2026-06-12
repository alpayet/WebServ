/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RoutePolicy.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 10:05:20 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:07:45 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTEPOLICY_HPP
#define ROUTEPOLICY_HPP

#include <string>
#include <vector>

namespace app {
struct RoutePolicy
{
	std::string				 rootPath;
	bool					 isListingEnabled;
	std::string				 defaultIndex;
	std::vector<std::string> allowedMethods;
};
} // namespace app

#endif // ROUTEPOLICY_HPP