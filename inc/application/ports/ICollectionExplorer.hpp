/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICollectionExplorer.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 22:47:28 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/30 17:00:36 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICOLLECTIONEXPLORER_HPP
#define ICOLLECTIONEXPLORER_HPP

#include <string>
#include <vector>

// TODO: faire implemeter
namespace app {
struct CollectionEntry
{
	std::string name;
	std::string lastMod;
	std::string size;
	std::string id;
};

class ICollectionExplorer
{
  public:
	virtual ~ICollectionExplorer(void) {}

	virtual std::vector<CollectionEntry> listCollection(std::string const &resourcePath) = 0;
};
} // namespace app

#endif // ICOLLECTIONEXPLORER_HPP