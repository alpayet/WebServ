/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IDynamicResourceLocator.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 21:48:05 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/11 17:49:00 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IDYNAMICRESOURCELOCATOR_HPP
#define IDYNAMICRESOURCELOCATOR_HPP

#include <string>
// TODO: faire herité la config de cette interface

class IDynamicResourceLocator
{
  public:
	virtual ~IDynamicResourceLocator(void) {}

	virtual std::string locate(std::string const &id, std::string const &rootPath) const = 0;
};

#endif // IDYNAMICRESOURCELOCATOR_HPP