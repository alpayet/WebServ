/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IHttpVersionProvider.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 19:54:48 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/25 22:09:49 by alpayet          ###   ########.fr       */
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
	~IHttpVersionProvider(void) {}

	virtual std::string getHttpVersion(void) = 0;
};
} // namespace http

#endif // IHTTPVERSIONPROVIDER_HPP