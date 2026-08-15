/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticResource.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 15:32:01 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:35:06 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATICRESOURCE_HPP
#define STATICRESOURCE_HPP

#include "domain/value_objects/ResourceMetaData.hpp"
#include <string>

namespace webserv {
namespace domain {
class StaticResource
{
  public:
	StaticResource(std::string const &id, ResourceMetaData const &metaData);

	std::string const &getId(void) const;
	std::string const &getResourcePath(void) const;
	std::size_t		   getResourceSize(void) const;

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
} // namespace webserv

#endif // STATICRESOURCE_HPP