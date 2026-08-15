/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DirectoryExplorer.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 01:29:19 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:23:45 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEINFOS_HPP
#define FILEINFOS_HPP

#include "application/ports/ICollectionExplorer.hpp"

namespace webserv {
namespace fileSystem {

class DirectoryExplorer : public app::ICollectionExplorer
{
  public:
	virtual ~DirectoryExplorer(void) {}

	virtual std::vector<app::CollectionEntry> listCollection(
		std::string const &resourcePath,
		std::string const &matchedRoute,
		std::string const &rootPath
	);
};
} // namespace fileSystem
}

#endif // FILEINFOS_HPP