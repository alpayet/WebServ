/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteStaticResourcePresenter.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:57:56 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/08 23:45:25 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/presenters/DeleteStaticResourcePresenter.hpp"
#include "infrastructure/http/presenters/success_lookup.hpp"
#include "infrastructure/http/response/Response.hpp"
#include <sstream>

namespace http {
DeleteStaticResourcePresenter::ViewModel const &
DeleteStaticResourcePresenter::getViewModel(void) const
{
	return (_viewModel);
}

void DeleteStaticResourcePresenter::presentDeletedResource(app::ResourceStatus status)
{
	Response::Builder response_builder;

	response_builder.withStatusLine(to_status_code(status));

	_viewModel.response = response_builder.build();
}
} // namespace http