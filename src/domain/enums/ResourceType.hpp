/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceType.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:40:38 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:35:31 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCETYPE_HPP
#define RESOURCETYPE_HPP

namespace webserv {
namespace domain {
enum ResourceType
{
	LEAF,
	COLLECTION,
	UNKNOWN
};
} // namespace domain
} // namespace webserv

#endif // RESOURCETYPE_HPP
