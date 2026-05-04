/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestEntity.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:58:22 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/04 16:00:54 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "domain/entities/RequestEntity.hpp"

RequestEntity::RequestEntity(std::string const &target, std::string const &protocol,
	std::map<std::string, std::string> const &headers) :
	_target(target),
	_protocol(protocol),
	_headers(headers)
{}