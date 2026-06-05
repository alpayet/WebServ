/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticResource.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 21:45:34 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/04 23:01:57 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/entities/StaticResource.hpp"

StaticResource::StaticResource() : _id(), _dataSource(NULL) {}

StaticResource::StaticResource(const std::string &id, IDataSource *dataSource)
	: _id(id), _dataSource(dataSource)
{
}

StaticResource::~StaticResource() { delete _dataSource; }

std::string const &StaticResource::getId(void) const { return (_id); }

IDataSource const *StaticResource::getDataSource(void) const { return (_dataSource); }

void StaticResource::init(std::string const &id, IDataSource *dataSource)
{
	delete _dataSource;
	_id = id;
	_dataSource = dataSource;
}