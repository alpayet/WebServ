/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourcePermissions.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:38:25 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/13 02:07:21 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace domain {
enum ResourcePermissions
{
	none = 0,
	readable = 1 << 0,
	writable = 1 << 1,
	executable = 1 << 2
};
} // namespace domain
