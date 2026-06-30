/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileInfos.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 01:29:19 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/30 17:09:19 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEINFOS_HPP
#define FILEINFOS_HPP

#include "application/ports/ICollectionExplorer.hpp"

namespace fileSystem {

class DirectoryExplorer
{
  public:
	virtual ~DirectoryExplorer(void) {}
	virtual std::vector<app::CollectionEntry> listCollection(std::string const &resourcePath);
};
} // namespace fileSystem

#endif // FILEINFOS_HPP