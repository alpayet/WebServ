/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IStaticResourceLocator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 03:30:53 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/11 17:50:28 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ISTATICRESOURCELOCATOR_HPP
#define ISTATICRESOURCELOCATOR_HPP

#include <string>
// TODO: faire herité la config de cette interface

class IStaticResourceLocator
{
  public:
	virtual ~IStaticResourceLocator(void) {}

	virtual std::string locate(std::string const &id, std::string const &rootPath) const = 0;
};

#endif // ISTATICRESOURCELOCATOR_HPP