/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_status_reason.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 21:41:14 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:18:06 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPSTATUSREASON_HPP
#define HTTPSTATUSREASON_HPP

#include <string>

namespace webserv {
namespace http {
char const *get_status_reason(unsigned short status_code);
} // namespace http
} // namespace webserv

#endif // HTTPSTATUSREASON_HPP