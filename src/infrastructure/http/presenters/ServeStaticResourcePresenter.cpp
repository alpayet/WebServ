/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourcePresenter.cpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:58:22 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/30 20:23:39 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/presenters/ServeStaticResourcePresenter.hpp"
#include "infrastructure/http/constants.hpp"
#include "infrastructure/http/presenters/listingHtml.hpp"
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
	app::ResourceStatus const				 status,
	std::string const						&id,
	std::vector<app::CollectionEntry> const &collectionData
)
{
	std::string const &listing_html = getListing(id, collectionData);

	std::stringstream contentLengthAsString;
	contentLengthAsString << listing_html.size();

	Response::Builder response_builder;

	response_builder.withStatusCode(toHttpCode(status));
	response_builder.withHeader(header::CONTENT_LENGTH, contentLengthAsString.str());
	response_builder.withBody(std::vector<char>(listing_html.begin(), listing_html.end()));

	_viewModel.response = response_builder.build();
	_viewModel.reader = NULL;
}
} // namespace http
