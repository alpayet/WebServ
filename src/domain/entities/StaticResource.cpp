/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticResource.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 21:45:34 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/09 22:22:59 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/entities/StaticResource.hpp"

StaticResource::StaticResource(std::string const &id, std::string const &storagePath)
	: _id(id), _storagePath(storagePath)
{
}

std::string const &StaticResource::getId(void) const { return (_id); }

std::string const &StaticResource::getstoragePath(void) const { return (_storagePath); }
