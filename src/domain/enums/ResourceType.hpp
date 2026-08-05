/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceType.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:40:38 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/04 19:22:25 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCETYPE_HPP
#define RESOURCETYPE_HPP

namespace domain {
enum ResourceType
{
	LEAF,
	COLLECTION,
	UNKNOWN
};
} // namespace domain

#endif // RESOURCETYPE_HPP
