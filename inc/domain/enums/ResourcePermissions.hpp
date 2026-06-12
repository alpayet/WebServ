/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourcePermissions.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:38:25 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:12:43 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace domain {
enum ResourcePermissions
{
	None = 0,
	Readable = 1 << 0,
	Writable = 1 << 1,
	Executable = 1 << 2
};
} // namespace domain
