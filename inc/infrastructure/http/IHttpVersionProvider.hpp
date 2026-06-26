/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IHttpVersionProvider.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 19:54:48 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/26 23:26:09 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IHTTPVERSIONPROVIDER_HPP
#define IHTTPVERSIONPROVIDER_HPP

#include <string>

// TODO: faire herité la config de cette interface

namespace http {
class IHttpVersionProvider
{
  public:
	virtual ~IHttpVersionProvider(void) = 0;

	virtual std::string getHttpVersion(void) const = 0;
};
} // namespace http

#endif // IHTTPVERSIONPROVIDER_HPP