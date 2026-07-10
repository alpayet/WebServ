/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICollectionExplorer.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 22:47:28 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/30 19:06:01 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICOLLECTIONEXPLORER_HPP
#define ICOLLECTIONEXPLORER_HPP

#include "application/ports/CollectionEntry.hpp"
#include <string>
#include <vector>

// TODO: faire implemeter
namespace app {

class ICollectionExplorer
{
  public:
	virtual ~ICollectionExplorer(void) {}

	virtual std::vector<CollectionEntry> listCollection(
		std::string const &resourcePath,
		std::string const &matchedRoute,
		std::string const &rootPath
	) = 0;
};
} // namespace app

#endif // ICOLLECTIONEXPLORER_HPP