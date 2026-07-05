/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Storage.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 04:41:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/05 03:24:41 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/storage/file_system/Storage.hpp"
#include "application/Exception.hpp"
#include "infrastructure/storage/file_system/Reader.hpp"
#include <cerrno>

namespace fileSystem {

void Storage::remove(std::string const &resourcePath)
{
	if (std::remove(resourcePath.c_str()) == 0)
		return;
	switch (errno)
	{
		case ENOENT:
			throw app::Exception(app::Exception::notFound);
			break;
		case EACCES:
		case EPERM:
			throw app::Exception(app::Exception::accessDenied);
			break;
		default:
			throw app::Exception(app::Exception::deleteFailed);
			break;
	}
}

app::IResourceReader *Storage::createReader(std::string const &resourcePath)
{
	return (new Reader(resourcePath));
}
} // namespace fileSystem
