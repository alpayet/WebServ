/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SystemResourceInfo.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 18:29:10 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:37:37 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSTEMRESOURCEINFO_HPP
#define SYSTEMRESOURCEINFO_HPP

#include "domain/enums/ResourcePermissions.hpp"
#include "domain/enums/ResourceType.hpp"
#include <string>

namespace webserv {
namespace app {
struct SystemResourceInfo
{
	std::string					resourcePath;
	domain::ResourceType		type;
	domain::ResourcePermissions permissions;
	std::size_t					resourceSize;
	bool						canBeDeleted;
	bool						exists;

	SystemResourceInfo() : resourceSize(0), canBeDeleted(false), exists(false) {};
};
} // namespace app
} // namespace webserv

#endif // SYSTEMRESOURCEINFO_HPP