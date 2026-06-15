/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SystemResourceInfos.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 19:48:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/15 23:39:15 by alpayet          ###   ########.fr       */
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
	std::size_t					contentlength;
	bool						canBeDeleted;
	bool						exists;
};
} // namespace app

#endif // SYSTEMSTATICRESOURCEINFO_HPP