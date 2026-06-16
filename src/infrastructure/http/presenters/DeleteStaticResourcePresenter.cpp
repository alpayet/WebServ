/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResourcePresenter.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:57:56 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/16 21:58:05 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DeleteStaticResourcePresenter.hpp"

DeleteStaticResourcePresenter::DeleteStaticResourcePresenter(void) {}

DeleteStaticResourcePresenter::DeleteStaticResourcePresenter(
	DeleteStaticResourcePresenter const &src
)
{
	*this = src;
}

DeleteStaticResourcePresenter::~DeleteStaticResourcePresenter(void) {}

DeleteStaticResourcePresenter &
DeleteStaticResourcePresenter::operator=(DeleteStaticResourcePresenter const &rhs)
{
	if (this != &rhs)
	{
		//
	}
	return (*this);
}