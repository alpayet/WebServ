/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourcePresenter.cpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:58:22 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/29 02:56:05 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/presenters/ServeStaticResourcePresenter.hpp"
#include "infrastructure/http/constants.hpp"
#include "infrastructure/http/response/Response.hpp"
#include <sstream>

namespace http {

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
	unsigned short statusCode;

	switch (resourceStatus)
	{
		case app::resourceFound:
			statusCode = 200;
			break;
		default:
			break;
	}

	std::stringstream contentLengthAsString;
	contentLengthAsString << resourceSize;

	Response::Builder response_builder;

	response_builder.withStatusCode(statusCode);
	response_builder.withHeader(header::CONTENT_LENGTH, contentLengthAsString.str());

	_viewModel.response = response_builder.build();
	_viewModel.reader = resourceReader;
}

void ServeStaticResourcePresenter::presentListing(
	app::ResourceStatus const resourceStatus, std::vector<char> const &CollectionData
)
{}
} // namespace http
