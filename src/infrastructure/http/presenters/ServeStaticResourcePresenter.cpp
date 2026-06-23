/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourcePresenter.cpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:58:22 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/22 21:34:20 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/presenters/ServeStaticResourcePresenter.hpp"
#include "infrastructure/http/Constants.hpp"
#include "infrastructure/http/messages/HeaderBlockSerializer.hpp"
#include "infrastructure/http/messages/Response.hpp"
#include <sstream>

namespace http {

ServeStaticResourcePresenter::ServeStaticResourcePresenter(std::string const &httpVersion)
	: _httpVersion(httpVersion)
{}

ServeStaticResourcePresenter::ViewModel const &
ServeStaticResourcePresenter::getViewModel(void) const
{
	return (_viewModel);
}

void ServeStaticResourcePresenter::presentContent(
	app::ResourceStatus const resourceStatus,
	std::size_t const		  resourceSize,
	app::IResourceReader	 *resourceReader
)
{
	Response::Status responseStatus;

	switch (resourceStatus)
	{
		case app::resourceFound:
			responseStatus.statusCode = 200;
			responseStatus.reason = "OK";
			break;
		default:
			break;
	}

	std::stringstream contentLengthAsString;
	contentLengthAsString << resourceSize;

	Response::Builder response_builder;

	response_builder.withProtocol(_httpVersion);
	response_builder.withStatus(responseStatus);
	response_builder.withHeader(header::CONTENT_LENGTH, contentLengthAsString.str());
	Response const &response = response_builder.build();

	_viewModel.rawHeaderBlock = HeaderBlockSerializer::serialize(response);
	_viewModel.reader = resourceReader;
}

void ServeStaticResourcePresenter::presentListing(
	app::ResourceStatus const resourceStatus, std::vector<char> const &CollectionData
)
{}
} // namespace http
