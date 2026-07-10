/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IValidationPolicy.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 18:25:42 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/06 21:00:59 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPIREQUESTVALIDATIONPOLICY_HPP
#define HTTPIREQUESTVALIDATIONPOLICY_HPP

#include <string>

namespace parse {
class IValidationPolicy
{
  public:
	virtual ~IValidationPolicy(void) {};

	virtual std::size_t getMaxRequestLineSize(void) const = 0;
	virtual std::size_t getMaxHeaderLineSize(void) const = 0;
	virtual std::size_t getMaxHeaderCount(void) const = 0;
	virtual std::size_t getMaxBodySize(void) const = 0;
};
} // namespace parse

#endif // HTTPIREQUESTVALIDATIONPOLICY_HPP