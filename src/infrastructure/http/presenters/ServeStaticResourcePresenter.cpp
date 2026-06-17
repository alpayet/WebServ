/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourcePresenter.cpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:58:22 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/17 04:14:15 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/presenters/ServeStaticResourcePresenter.hpp"

namespace http {

Response const &ServeStaticResourcePresenter::getResponse() const { return (_response); }

void ServeStaticResourcePresenter::presentContent(
	app::ResourceStatus status, app::IResourceReader *resourceReader
)
{
	switch (status)
	{
		case app::resourceFound:

			break;

		default:
			break;
	}
}

void ServeStaticResourcePresenter::presentListing(
	app::ResourceStatus status, std::vector<char> CollectionData
)
{}
} // namespace http
