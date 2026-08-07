/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 20:23:53 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/05 20:42:48 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/constants.hpp"

namespace headers {
char const CONTENT_LENGTH[] = "content-length";
char const CONTENT_TYPE[] = "content-type";
char const CONNECTION[] = "connection";
char const COOKIE[] = "cookie";
char const SET_COOKIE[] = "set-cookie";
char const STATUS[] = "status";
char const LOCATION[] = "location";

} // namespace headers