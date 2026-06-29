/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SystemResourceInfos.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 19:48:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/29 01:17:01 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSTEMSTATICRESOURCEINFO_HPP
#define SYSTEMSTATICRESOURCEINFO_HPP

#include "domain/enums/ResourcePermissions.hpp"
#include "domain/enums/ResourceType.hpp"
#include <string>

namespace app {
struct SystemResourceInfos
{
	// TODO: check si le root est bien au debut de resourcePath pour empecher le traversal ../app/
	std::string					resourcePath;
	domain::ResourceType		type;
	domain::ResourcePermissions permissions;
	std::size_t					resourceSize;
	bool						canBeDeleted;
	bool						exists;

	SystemResourceInfos() : resourceSize(0), canBeDeleted(false), exists(false) {};
};
} // namespace app

#endif // SYSTEMSTATICRESOURCEINFO_HPP