/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICollectionExplorer.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 22:47:28 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/16 22:49:53 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICOLLECTIONEXPLORER_HPP
#define ICOLLECTIONEXPLORER_HPP

#include <string>
#include <vector>

// TODO: faire implemeter
namespace app {
class ICollectionExplorer
{
  public:
	virtual ~ICollectionExplorer(void) {}

	virtual std::vector<char> listingCollection(std::string const &resourcePath) = 0;
};
} // namespace app

#endif // ICOLLECTIONEXPLORER_HPP