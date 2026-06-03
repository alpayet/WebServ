/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IStaticFileRepository.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 04:12:08 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/02 13:56:23 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ISTATICFILEREPOSITORY_HPP
#define ISTATICFILEREPOSITORY_HPP

#include <string>

class StaticFile;

class IStaticFileRepository
{
  public:
	virtual ~IStaticFileRepository(void) {}

	virtual void save(StaticFile const &file) = 0;
};

#endif // ISTATICFILEREPOSITORY_HPP