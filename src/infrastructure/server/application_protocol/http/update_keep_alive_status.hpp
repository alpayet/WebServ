/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_keep_alive_status.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 15:44:29 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:21:12 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPUPDATEKEEPALIVESTATUS_HPP
#define HTTPUPDATEKEEPALIVESTATUS_HPP

#include "infrastructure/server/application_protocol/http/core/Context.hpp"
#include "infrastructure/server/application_protocol/http/request/Request.hpp"

namespace webserv {
namespace http {
void update_keep_alive_status(Context &context);
} // namespace http
}

#endif // HTTPUPDATEKEEPALIVESTATUS_HPP
