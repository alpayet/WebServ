/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 03:46:22 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/11 20:39:05 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgi/constants.hpp"

namespace cgi {
namespace meta {
char const CONTENT_LENGTH[] = "CONTENT_LENGTH";
char const CONTENT_TYPE[] = "CONTENT_TYPE";
char const REQUEST_METHOD[] = "REQUEST_METHOD";
char const QUERY_STRING[] = "QUERY_STRING";
char const HTTP_COOKIE[] = "HTTP_COOKIE";
} // namespace meta
} // namespace cgi
