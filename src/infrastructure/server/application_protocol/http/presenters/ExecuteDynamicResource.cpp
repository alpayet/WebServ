/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteDynamicResource.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 21:53:25 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/09 22:12:14 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/presenters/ExecuteDynamicResource.hpp"
#include "infrastructure/server/application_protocol/http/presenters/success_lookup.hpp"
#include "infrastructure/server/application_protocol/http/response/Response.hpp"
#include <sstream>

namespace http {
namespace presenter {

ExecuteDynamicResource::ViewModel const &
ExecuteDynamicResource::getViewModel(void) const {
  return (_viewModel);
}

void ExecuteDynamicResource::presentStream(
    const app::StreamResources resources) {
  _viewModel.stream_resources = resources;
}
} // namespace presenter

} // namespace http