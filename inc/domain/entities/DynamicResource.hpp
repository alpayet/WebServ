/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DynamicResource.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:14:21 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/10 01:11:29 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNAMICRESOURCE_HPP
#define DYNAMICRESOURCE_HPP

#include <map>
#include <string>

class DynamicResource
{
  public:
	DynamicResource(std::string const &id, std::string const &storagePath);

	std::string const &getId(void) const;
	std::string const &getstoragePath(void) const;

  private:
	std::string _id;
	std::string _storagePath;
};

#endif // DYNAMICRESOURCE_HPP