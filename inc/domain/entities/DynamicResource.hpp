/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DynamicResource.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:14:21 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/12 18:12:11 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNAMICRESOURCE_HPP
#define DYNAMICRESOURCE_HPP

#include <map>
#include <string>

namespace domain {
class DynamicResource
{
  public:
	DynamicResource(std::string const &id, std::string const &storagePath);

	std::string const &getId(void) const;
	std::string const &getstoragePath(void) const;

  private:
	DynamicResource(DynamicResource const &src);
	DynamicResource &operator=(DynamicResource const &rhs);

	std::string _id;
	std::string _storagePath;
};
} // namespace domain

#endif // DYNAMICRESOURCE_HPP