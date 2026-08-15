/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 20:23:53 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:22:43 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/constants.hpp"

namespace webserv {
namespace headers {
char const CONTENT_LENGTH[] = "content-length";
char const CONTENT_TYPE[] = "content-type";
char const CONNECTION[] = "connection";
char const COOKIE[] = "cookie";
char const SET_COOKIE[] = "set-cookie";
char const STATUS[] = "status";
char const LOCATION[] = "location";

} // namespace headers
}