/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResourcePresenter.cpp                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:58:10 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/01 01:51:44 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/presenters/ExecuteDynamicResourcePresenter.hpp"

namespace http {

ExecuteDynamicResourcePresenter::ViewModel const &
ExecuteDynamicResourcePresenter::getViewModel(void) const
{
	return (_viewModel);
}

void ExecuteDynamicResourcePresenter::presentDynamicContent(app::IResourceReader *resourceReader)
{
	_viewModel.reader = resourceReader;
}
} // namespace http
