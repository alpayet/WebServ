/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRouteAccessValidator.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 17:40:14 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/01 21:35:00 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPIROUTEACCESSVALIDATOR_HPP
#define HTTPIROUTEACCESSVALIDATOR_HPP

// TODO: faire herité la config de cette interface
#include <string>
#include <vector>

namespace http
{
	class IRouteAccessValidator
	{
	  public:
		virtual ~IRouteAccessValidator(void) {}

		virtual std::vector<std::string> getAllowedMethods(std::string const &uri) const = 0;
	};
} // namespace http

#endif // HTTPIROUTEACCESSVALIDATOR_HPP