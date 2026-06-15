/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IStaticResourceStorage.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 04:10:04 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/15 23:39:09 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ISTATICRESOURCESTORAGE_HPP
#define ISTATICRESOURCESTORAGE_HPP

#include <string>

namespace app {
class IStaticResourceReader;

class IStaticResourceStorage
{
  public:
	virtual ~IStaticResourceStorage(void) {}

	virtual IStaticResourceReader *createReader(std::string const &resourcePath) = 0;
	virtual void				   remove(std::string const &resourcePath) = 0;
};
} // namespace app

#endif // ISTATICRESOURCESTORAGE_HPP