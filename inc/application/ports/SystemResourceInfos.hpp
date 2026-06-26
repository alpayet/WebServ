/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SystemResourceInfos.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 19:48:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/26 03:43:07 by alpayet          ###   ########.fr       */
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
	// TODO: check si / la fin dans le cas dun dossier (a voir)
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