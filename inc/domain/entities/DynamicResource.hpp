/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DynamicResource.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 00:14:21 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/09 00:41:07 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNAMICRESOURCE_HPP
#define DYNAMICRESOURCE_HPP

#include <map>
#include <string>

class DynamicResource
{
  public:
	DynamicResource(
		std::string const						 &id,
		std::string const						 &storageLocation,
		std::map<std::string, std::string> const &environment
	);

	std::string const						 &getId(void) const;
	std::string const						 &getStorageLocation(void) const;
	std::map<std::string, std::string> const &getEnvironment(void) const;

  private:
	std::string _id;
	std::string _storageLocation;
};

#endif // DYNAMICRESOURCE_HPP