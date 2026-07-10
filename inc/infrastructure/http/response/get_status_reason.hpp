/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_status_reason.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 21:41:14 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/06 05:29:20 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPSTATUSREASON_HPP
#define HTTPSTATUSREASON_HPP

#include <string>

namespace http {
char const *get_status_reason(unsigned short status_code);
} // namespace http

#endif // HTTPSTATUSREASON_HPP