/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   success_lookup.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 20:37:55 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:15:45 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUCCESSLOOKUP_HPP
#define SUCCESSLOOKUP_HPP

#include "application/ResourceStatus.hpp"
#include <map>

namespace webserv {
namespace http {
unsigned short to_status_code(app::ResourceStatus status);
} // namespace http
} // namespace webserv

#endif // SUCCESSLOOKUP_HPP