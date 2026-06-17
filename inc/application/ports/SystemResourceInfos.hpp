/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SystemResourceInfos.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 19:48:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/18 00:18:58 by alpayet          ###   ########.fr       */
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
	std::string resourcePath;
	// TODO: utiliser methodes de archi/storage/file_system
	domain::ResourceType		type;
	domain::ResourcePermissions permissions;
	std::size_t					resourceSize;
	bool						canBeDeleted;
	bool						exists;
};
} // namespace app

#endif // SYSTEMSTATICRESOURCEINFO_HPP