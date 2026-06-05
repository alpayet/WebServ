/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FindStaticResourceUseCase.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:27:44 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/05 16:29:31 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application/use_cases/find_static_resource/FindStaticResourceUseCase.hpp"

FindStaticResourceUseCase::FindStaticResourceUseCase(void) {}

FindStaticResourceUseCase::FindStaticResourceUseCase(const FindStaticResourceUseCase &src)
{
	*this = src;
}

FindStaticResourceUseCase::~FindStaticResourceUseCase(void) {}

FindStaticResourceUseCase &
FindStaticResourceUseCase::operator=(FindStaticResourceUseCase const &rhs)
{
	if (this != &rhs)
	{
		//
	}
	return (*this);
}