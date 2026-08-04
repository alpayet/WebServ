/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updateKeepAliveStatus.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 15:44:29 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/04 15:49:48 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPUPDATEKEEPALIVESTATUS_HPP
#define HTTPUPDATEKEEPALIVESTATUS_HPP

#include "infrastructure/http/request/Request.hpp"
#include "infrastructure/http/Context.hpp"

namespace http {
void updateKeepAliveStatus(Context &context);
} // namespace http

#endif // HTTPUPDATEKEEPALIVESTATUS_HPP
