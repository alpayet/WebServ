/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SystemResourceInfos.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 19:48:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/16 16:49:25 by mlouis           ###   ########.fr       */
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
	std::string					resourcePath;
	domain::ResourceType		type;
	domain::ResourcePermissions permissions;
	std::size_t					contentLength;
	bool						canBeDeleted;
	bool						exists;
};
} // namespace app

#endif // SYSTEMSTATICRESOURCEINFO_HPP