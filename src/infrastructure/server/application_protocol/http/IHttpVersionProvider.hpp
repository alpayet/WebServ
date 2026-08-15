/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IHttpVersionProvider.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 19:54:48 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 15:40:47 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IHTTPVERSIONPROVIDER_HPP
#define IHTTPVERSIONPROVIDER_HPP

#include <string>

namespace webserv {
namespace http {
class IHttpVersionProvider
{
  public:
	virtual ~IHttpVersionProvider(void) {};

	virtual std::string getHttpVersion(void) const = 0;
	virtual bool 		isSupportedHttpVersion(std::string const &version) const = 0;
};
} // namespace http
}

#endif // IHTTPVERSIONPROVIDER_HPP