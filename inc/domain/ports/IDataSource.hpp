/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IDataSource.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 15:59:27 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/02 16:11:54 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IDATASOURCE_HPP
#define IDATASOURCE_HPP

#include <vector>

class IDataSource
{
  public:
	virtual ~IDataSource(void) {}

	virtual std::vector<char> readAll(void) const = 0;
};

#endif // IDATASOURCE_HPP