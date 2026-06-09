/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IStaticResourceStorage.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 04:10:04 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/09 04:38:07 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ISTATICRESOURCESTORAGE_HPP
#define ISTATICRESOURCESTORAGE_HPP

#include <string>

class IResourceReader;

class IStaticResourceStorage
{
  public:
	virtual ~IStaticResourceStorage(void) {}

	virtual IResourceReader *createReader(std::string const &storageLocation) = 0;
	virtual void			 remove(std::string const &storageLocation) = 0;
};

#endif // ISTATICRESOURCESTORAGE_HPP