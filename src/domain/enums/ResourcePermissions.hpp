/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourcePermissions.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:38:25 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:35:13 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCEPERMISSIONS_HPP
#define RESOURCEPERMISSIONS_HPP

namespace webserv {
namespace domain {
enum ResourcePermissions
{
	NONE = 0,
	READABLE = 1 << 0,
	WRITABLE = 1 << 1,
	EXECUTABLE = 1 << 2
};
} // namespace domain
}

#endif // RESOURCEPERMISSIONS_HPP
