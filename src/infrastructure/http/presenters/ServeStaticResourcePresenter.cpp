/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServeStaticResourcePresenter.cpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 21:58:22 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/16 22:59:26 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/presenters/ServeStaticResourcePresenter.hpp"

namespace http {

Response const &ServeStaticResourcePresenter::getResponse() const { return (_response); }

void ServeStaticResourcePresenter::presentContent(app::IStaticResourceReader *resourceReader) {}

void ServeStaticResourcePresenter::presentListing(std::vector<char> CollectionData) {}
} // namespace http
