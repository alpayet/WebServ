/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRequestValidationPolicy.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 18:25:42 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/09 13:15:15 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPIREQUESTVALIDATIONPOLICY_HPP
#define HTTPIREQUESTVALIDATIONPOLICY_HPP

// TODO: faire herité la config de cette interface
#include <string>

namespace http
{
	class IRequestValidationPolicy
	{
	  public:
		virtual ~IRequestValidationPolicy(void) {};

		virtual std::size_t getMaxBodySize() const = 0;
	};
} // namespace http

#endif // HTTPIREQUESTVALIDATIONPOLICY_HPP