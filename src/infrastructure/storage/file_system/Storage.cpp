/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Storage.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 04:41:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:24:48 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/storage/file_system/Storage.hpp"
#include "application/Exception.hpp"
#include "infrastructure/storage/file_system/Reader.hpp"
#include <cerrno>

namespace webserv {
namespace fileSystem {

void Storage::remove(std::string const &resourcePath)
{
	if (std::remove(resourcePath.c_str()) == 0)
		return;
	switch (errno)
	{
		case ENOENT:
			throw app::Exception(app::Exception::NOT_FOUND);
			break;
		case EACCES:
		case EPERM:
			throw app::Exception(app::Exception::ACCESS_DENIED);
			break;
		default:
			throw app::Exception(app::Exception::DELETE_FAILED);
			break;
	}
}

app::IResourceReader *Storage::createReader(std::string const &resourcePath)
{
	return (new Reader(resourcePath));
}
} // namespace fileSystem
} // namespace webserv
