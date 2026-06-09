/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticResource.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 15:32:01 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/09 22:22:57 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATICRESOURCE_HPP
#define STATICRESOURCE_HPP

#include <string>

class StaticResource
{
  public:
	StaticResource(std::string const &id, std::string const &storagePath);

	std::string const &getId(void) const;
	std::string const &getstoragePath(void) const;

  private:
	std::string _id;
	std::string _storagePath;
};

#endif // STATICRESOURCE_HPP