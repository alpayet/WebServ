/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CollectionEntry.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 18:31:02 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/30 18:31:27 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLECTIONENTRY_HPP
# define COLLECTIONENTRY_HPP

#include <string>

namespace app {
struct CollectionEntry
{
	std::string name;
	std::string lastMod;
	std::string size;
	std::string id;
};
}

#endif // COLLECTIONENTRY_HPP