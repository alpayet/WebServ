/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourcePresenter.cpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:58:22 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/18 16:20:56 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/presenters/ServeStaticResourcePresenter.hpp"
#include "infrastructure/http/Constants.hpp"
#include "infrastructure/http/messages/Response.hpp"
#include <sstream>

namespace http {

ServeStaticResourcePresenter::ViewModel const &
ServeStaticResourcePresenter::getViewModel(void) const
{
	return (_viewModel);
}

void ServeStaticResourcePresenter::presentContent(
	app::ResourceStatus const	resourceStatus,
	std::size_t const			resourceSize,
	app::IResourceReader const *resourceReader
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

	Response::Header header = {
		.name = header::CONTENT_LENGTH, .value = contentLengthAsString.str()
	};

	Response response;

	response.status = responseStatus;
	response.headers.insert(response.headers.end(), header);
}

void ServeStaticResourcePresenter::presentListing(
	app::ResourceStatus const resourceStatus, std::vector<char> const &CollectionData
)
{}
} // namespace http
