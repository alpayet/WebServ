/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceType.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:40:38 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/27 07:07:03 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCETYPE_HPP
#define RESOURCETYPE_HPP

namespace domain {
enum ResourceType
{
	leaf,
	collection,
	unknown
};
} // namespace domain

#endif // RESOURCETYPE_HPP
