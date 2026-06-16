/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourcePresenter.cpp                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:58:10 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/16 21:58:15 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ExecuteDynamicResourcePresenter.hpp"

ExecuteDynamicResourcePresenter::ExecuteDynamicResourcePresenter(void) {}

ExecuteDynamicResourcePresenter::ExecuteDynamicResourcePresenter(
	ExecuteDynamicResourcePresenter const &src
)
{
	*this = src;
}

ExecuteDynamicResourcePresenter::~ExecuteDynamicResourcePresenter(void) {}

ExecuteDynamicResourcePresenter &
ExecuteDynamicResourcePresenter::operator=(ExecuteDynamicResourcePresenter const &rhs)
{
	if (this != &rhs)
	{
		//
	}
	return (*this);
}