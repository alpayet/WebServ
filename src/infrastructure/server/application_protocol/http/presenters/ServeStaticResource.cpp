/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResource.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:58:22 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/09 22:08:42 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/presenters/ServeStaticResource.hpp"
#include "infrastructure/server/application_protocol/http/presenters/get_listing_html.hpp"
#include "infrastructure/server/application_protocol/http/presenters/success_lookup.hpp"
#include "infrastructure/server/application_protocol/http/response/Response.hpp"

namespace http {
namespace presenter {

ServeStaticResource::ViewModel const &ServeStaticResource::getViewModel(void) const
{
	return (_viewModel);
}

void ServeStaticResource::presentStaticContent(
	app::ResourceStatus status, std::size_t resourceSize, app::IResourceReader *resourceReader
)
{
	Response::Builder builder;

	builder.withStatusLine(to_status_code(status));
	builder.withContentLength(resourceSize);

	_viewModel.response = builder.build();
	_viewModel.reader = resourceReader;
}

void ServeStaticResource::presentListing(
	app::ResourceStatus						 status,
	std::string const						&id,
	std::vector<app::CollectionEntry> const &collectionData
)
{
	std::string const &listing_html = get_listing_html(id, collectionData);

	Response::Builder builder;

	builder.withStatusLine(to_status_code(status));
	builder.withContentLength(listing_html.size());
	builder.withBody(listing_html);

	_viewModel.response = builder.build();
	_viewModel.reader = NULL;
}
} // namespace presenter

} // namespace http
