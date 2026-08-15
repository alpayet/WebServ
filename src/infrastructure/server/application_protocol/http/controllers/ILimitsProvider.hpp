/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ILimitsProvider.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 03:13:02 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:09:14 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ILIMITSPROVIDER_HPP
#define ILIMITSPROVIDER_HPP

#include <string>

namespace webserv {
namespace http {
class ILimitsProvider
{
  public:
	virtual ~ILimitsProvider(void) {}

	virtual std::size_t getMaxBodySize(std::string const &uri) const = 0;
};
} // namespace http
} // namespace webserv

#endif // ILIMITSPROVIDER_HPP