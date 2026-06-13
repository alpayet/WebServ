/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticResource.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 15:32:01 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/13 03:44:44 by alpayet          ###   ########.fr       */
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
	enum HandlingIntent
	{
		serveContent,
		serveIndex,
		generateListing
	};

  public:
	StaticResource(
		std::string const	   &id,
		std::string const	   &rootPath,
		bool const				isListingEnabled,
		ResourceMetaData const &targetMetaData,
		ResourceMetaData const &indexMetaData
	);

	std::string const &getStoragePath(void) const;

	bool shouldServeContent(void) const;
	bool shouldServeIndex(void) const;
	bool shouldGenerateListing(void) const;

  private:
	StaticResource(StaticResource const &src);
	StaticResource &operator=(StaticResource const &rhs);

	std::string		 _id;
	HandlingIntent	 _intent;
	ResourceMetaData _metaData;
};
} // namespace domain

#endif // STATICRESOURCE_HPP