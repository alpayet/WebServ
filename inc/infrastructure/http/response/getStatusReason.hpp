/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statusReason.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 21:41:14 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/06 01:41:30 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPSTATUSREASON_HPP
#define HTTPSTATUSREASON_HPP

#include <string>

namespace http {
char const *getStatusReason(unsigned short statusCode);
} // namespace http

#endif // HTTPSTATUSREASON_HPP