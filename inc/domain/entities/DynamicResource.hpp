/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DynamicResource.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:14:21 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/01 04:13:11 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNAMICRESOURCE_HPP
#define DYNAMICRESOURCE_HPP

#include "domain/value_objects/ResourceMetaData.hpp"
#include <string>

namespace domain {
class DynamicResource
{
  public:
	DynamicResource(std::string const &id, ResourceMetaData const &metaData);

	std::string const &getResourcePath(void) const;

	bool isReadable(void) const;
	bool isExecutable(void) const;

  private:
	DynamicResource(DynamicResource const &src);
	DynamicResource &operator=(DynamicResource const &rhs);

	std::string		 _id;
	ResourceMetaData _metaData;
};
} // namespace domain

#endif // DYNAMICRESOURCE_HPP