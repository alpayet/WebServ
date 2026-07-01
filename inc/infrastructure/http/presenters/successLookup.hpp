/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   successLookup.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 20:37:55 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/01 03:38:43 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUCCESSLOOKUP_HPP
#define SUCCESSLOOKUP_HPP

#include "application/ResourceStatus.hpp"
#include <map>

namespace http {
unsigned short toHttpStatusCode(app::ResourceStatus const status);
} // namespace http

#endif // SUCCESSLOOKUP_HPP