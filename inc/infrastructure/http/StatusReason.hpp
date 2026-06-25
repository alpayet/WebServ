/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusReason.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 21:41:14 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/25 22:01:30 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPSTATUSREASON_HPP
#define HTTPSTATUSREASON_HPP

#include <string>

namespace http {

static char const REASON_200[] = "OK";
static char const NO_REASON[] = "";

char const *getReasonPhrase(unsigned short statusCode);
} // namespace http

#endif // HTTPSTATUSREASON_HPP