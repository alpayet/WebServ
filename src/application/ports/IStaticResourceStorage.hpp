/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IStaticResourceStorage.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 04:10:04 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:37:31 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ISTATICRESOURCESTORAGE_HPP
#define ISTATICRESOURCESTORAGE_HPP

#include <string>

namespace webserv {
namespace app {
class IResourceReader;

class IStaticResourceStorage
{
  public:
	virtual ~IStaticResourceStorage(void) {}

	virtual IResourceReader *createReader(std::string const &resourcePath) = 0;
	virtual void			 remove(std::string const &resourcePath) = 0;
};
} // namespace app
} // namespace webserv

#endif // ISTATICRESOURCESTORAGE_HPP