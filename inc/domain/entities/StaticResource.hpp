/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticResource.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 15:32:01 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:12:30 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATICRESOURCE_HPP
#define STATICRESOURCE_HPP

#include "domain/enums/ResourcePermissions.hpp"
#include "domain/enums/ResourceType.hpp"
#include <string>

namespace domain {
class StaticResource
{
  public:
	enum HandlingIntent
	{
		ServeContent,
		ServeIndex,
		GenerateListing
	};

  public:
	StaticResource(
		std::string const		 &id,
		std::string const		  rootPath,
		std::string const		 &storagePath,
		ResourceType const		  type,
		ResourcePermissions const permissions,
		std::size_t const		  contentLenght
	);

	std::string const &getId(void) const;
	std::string const &getStoragePath(void) const;

  private:
	StaticResource(StaticResource const &src);
	StaticResource &operator=(StaticResource const &rhs);

	std::string			_id;
	std::string			_storagePath;
	HandlingIntent		_intent;
	std::size_t			_contentLenght;
	ResourcePermissions _permission;
};
} // namespace domain

#endif // STATICRESOURCE_HPP