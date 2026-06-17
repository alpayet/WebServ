/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourcePresenter.cpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:58:22 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/18 00:10:39 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/presenters/ServeStaticResourcePresenter.hpp"

namespace http {

ServeStaticResourcePresenter::ViewModel const &
ServeStaticResourcePresenter::getViewModel(void) const
{
	return (_viewModel);
}

void ServeStaticResourcePresenter::presentContent(
	app::ResourceStatus resourceStatus, app::IResourceReader *resourceReader
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
}

void ServeStaticResourcePresenter::presentListing(
	app::ResourceStatus resourceStatus, std::vector<char> CollectionData
)
{}
} // namespace http
