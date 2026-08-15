/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceStatus.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 02:17:25 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:38:58 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCESTATUS_HPP
#define RESOURCESTATUS_HPP

namespace webserv {
namespace app {
enum ResourceStatus
{
	FOUND,
	DELETED
};
} // namespace app
}

#endif // RESOURCESTATUS_HPP
