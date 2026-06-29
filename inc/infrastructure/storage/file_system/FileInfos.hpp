/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileInfos.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 01:29:19 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/30 01:33:46 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEINFOS_HPP
#define FILEINFOS_HPP

#include <string>
#include <vector>

namespace fileSystem {
struct FileInfos
{
	std::string name;
	std::string lastMod;
	std::string size;
	std::string uri;
};

std::vector<FileInfos> getFileInfos(
	std::string const &resPath, std::string const &matchedRoute, std::string const &rootPath
);
} // namespace fileSystem

#endif // FILEINFOS_HPP