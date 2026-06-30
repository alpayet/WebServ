/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourcePresenter.cpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:58:22 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/30 17:16:11 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/presenters/ServeStaticResourcePresenter.hpp"
#include "infrastructure/http/constants.hpp"
#include "infrastructure/http/presenters/successLookup.hpp"
#include "infrastructure/http/response/Response.hpp"
#include <sstream>

namespace http {

ServeStaticResourcePresenter::ViewModel const &
ServeStaticResourcePresenter::getViewModel(void) const
{
	return (_viewModel);
}

void ServeStaticResourcePresenter::presentContent(
	app::ResourceStatus const status,
	std::size_t const		  resourceSize,
	app::IResourceReader	 *resourceReader
)
{
	std::stringstream contentLengthAsString;
	contentLengthAsString << resourceSize;

	Response::Builder response_builder;

	response_builder.withStatusCode(toHttpCode(status));
	response_builder.withHeader(header::CONTENT_LENGTH, contentLengthAsString.str());

	_viewModel.response = response_builder.build();
	_viewModel.reader = resourceReader;
}

void ServeStaticResourcePresenter::presentListing(
	app::ResourceStatus const status, std::vector<char> const &CollectionData
)
{}
} // namespace http
