/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IStaticResourceRepository.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 04:12:08 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/04 01:02:25 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ISTATICFILEREPOSITORY_HPP
#define ISTATICFILEREPOSITORY_HPP

#include <string>

class StaticResource;

class IStaticResourceRepository
{
  public:
	virtual ~IStaticResourceRepository(void) {}

	virtual StaticResource const *findById(std::string const &id) = 0;
	virtual bool				  exists(std::string const &id) = 0;
	virtual void				  remove(std::string const &id) = 0;
};

#endif // ISTATICFILEREPOSITORY_HPP