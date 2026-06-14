/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticResource.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 15:32:01 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/14 15:09:49 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATICRESOURCE_HPP
#define STATICRESOURCE_HPP

#include "domain/value_objects/ResourceMetaData.hpp"
#include <string>

namespace domain {
class StaticResource
{
  public:
	StaticResource(
		std::string const &id, std::string const &rootPath, ResourceMetaData const &metaData
	);

	std::string const &getStoragePath(void) const;

	bool isReadable(void) const;
	bool isExecutable(void) const;

	bool canBeDeleted(void) const;

  private:
	StaticResource(StaticResource const &src);
	StaticResource &operator=(StaticResource const &rhs);

	std::string		 _id;
	ResourceMetaData _metaData;
};
} // namespace domain

#endif // STATICRESOURCE_HPP