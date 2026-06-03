/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticFile.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 21:45:34 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/04 01:00:39 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/entities/StaticResource.hpp"

StaticResource::StaticResource(const std::string &id, IDataSource *dataSource)
	: _id(id), _dataSource(dataSource)
{
}

std::string const &StaticResource::getId(void) const { return (_id); }

IDataSource const *StaticResource::getDataSource(void) const { return (_dataSource); }