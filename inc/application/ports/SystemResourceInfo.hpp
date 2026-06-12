/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SystemResourceInfo.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 19:48:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:07:47 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSTEMSTATICRESOURCEINFO_HPP
#define SYSTEMSTATICRESOURCEINFO_HPP

#include "domain/enums/ResourcePermissions.hpp"
#include "domain/enums/ResourceType.hpp"
#include <string>

namespace app {
struct SystemResourceInfo
{
	std::string			storagePath;
	ResourceType		type;
	ResourcePermissions permissions;
	std::size_t			contentLenght;
};
} // namespace app

#endif // SYSTEMSTATICRESOURCEINFO_HPP