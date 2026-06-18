/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IVersionProvider.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 19:54:48 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/18 19:59:10 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IHTTPVERSIONPROVIDER_HPP
#define IHTTPVERSIONPROVIDER_HPP

#include <string>

// TODO: faire herité la config de cette interface

namespace http {
class IVersionProvider
{
  public:
	~IVersionProvider(void) {}

	virtual std::string getHttpVersion(void) const = 0;
};
} // namespace http

#endif // IHTTPVERSIONPROVIDER_HPP