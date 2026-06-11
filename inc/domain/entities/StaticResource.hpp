/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticResource.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 15:32:01 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/11 19:43:03 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATICRESOURCE_HPP
#define STATICRESOURCE_HPP

#include <string>

class StaticResource
{
  public:
	enum HandlingIntent
	{
		ServeContent,
		ServeIndex,
		GenerateListing
	};

	enum Permission
	{
		None = 0,
		Readable = 1 << 0,
		Writable = 1 << 1,
		Executable = 1 << 2
	}

	public : StaticResource(std::string const &id, std::string const &storagePath);

	std::string const &getId(void) const;
	std::string const &getstoragePath(void) const;

  private:
	std::string	   _id;
	std::string	   _storagePath;
	HandlingIntent _intent;
	Permission	   _permission;
};

#endif // STATICRESOURCE_HPP