/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   success_lookup.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 20:37:55 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/29 21:04:02 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUCCESSLOOKUP_HPP
#define SUCCESSLOOKUP_HPP

#include "application/ResourceStatus.hpp"
#include <map>

namespace http {
extern std::map<app::ResourceStatus, unsigned short> const SUCCESS_LOOKUP;

unsigned short toHttpCode(app::ResourceStatus const status);
} // namespace http

#endif // SUCCESSLOOKUP_HPP