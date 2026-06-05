/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticResource.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 15:32:01 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/05 15:27:46 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATICRESOURCE_HPP
#define STATICRESOURCE_HPP

#include <string>

class IDataSource;

class StaticResource
{
  public:
	StaticResource(void);
	StaticResource(const std::string &id, IDataSource *dataSource);
	~StaticResource(void);

	std::string const &getId(void) const;
	IDataSource const *getDataSource(void) const;

	void StaticResource::init(std::string const &id, IDataSource *dataSource);

  private:
	StaticResource(StaticResource const &src);
	StaticResource &operator=(StaticResource const &rhs);

	std::string	 _id;
	IDataSource *_dataSource;
};

#endif // STATICRESOURCE_HPP