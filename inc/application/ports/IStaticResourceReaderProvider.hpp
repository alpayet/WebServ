/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IStaticResourceReaderProvider.hpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 00:04:13 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/07 00:15:46 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ISTATICRESOURCEREADERPROVIDER_HPP
#define ISTATICRESOURCEREADERPROVIDER_HPP

#include <string>

class IResourceReader;

class IStaticResourceReaderProvider
{
  public:
	virtual ~IStaticResourceReaderProvider(void) {}

	virtual IResourceReader *createReader(std::string const &id) = 0;
};

#endif // ISTATICRESOURCEREADERPROVIDER_HPP