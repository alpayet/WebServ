/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourcePresenter.cpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:58:22 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/03 23:31:12 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/presenters/ServeStaticResourcePresenter.hpp"
#include "infrastructure/http/constants.hpp"
#include "infrastructure/http/presenters/listingHtml.hpp"
#include "infrastructure/http/presenters/successLookup.hpp"
#include "infrastructure/http/response/Response.hpp"

namespace http {

ServeStaticResourcePresenter::ViewModel const &
ServeStaticResourcePresenter::getViewModel(void) const
{
	return (_viewModel);
}

void ServeStaticResourcePresenter::presentStaticContent(
	app::ResourceStatus const status,
	std::size_t const		  resourceSize,
	app::IResourceReader	 *resourceReader
)
{
	Response::Builder builder;

	builder.withStatusCode(toStatusCode(status));
	builder.withContentLength(resourceSize);

	_viewModel.response = builder.build();
	_viewModel.reader = resourceReader;
}

void ServeStaticResourcePresenter::presentListing(
	app::ResourceStatus const				 status,
	std::string const						&id,
	std::vector<app::CollectionEntry> const &collectionData
)
{
	std::string const &listing_html = getListing(id, collectionData);

	Response::Builder builder;

	builder.withStatusCode(toStatusCode(status));
	builder.withContentLength(listing_html.size());
	builder.withBody(listing_html);

	_viewModel.response = builder.build();
	_viewModel.reader = NULL;
}
} // namespace http
