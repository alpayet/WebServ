/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statusReason.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 21:41:14 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/30 00:00:17 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPSTATUSREASON_HPP
#define HTTPSTATUSREASON_HPP

#include <string>

namespace http {
char const *getReasonPhrase(unsigned short statusCode);
} // namespace http

#endif // HTTPSTATUSREASON_HPP