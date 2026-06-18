/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Constants.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 21:09:41 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/18 22:42:47 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace http {

static char const COLON = ':';
static char const SP = ' ';
static char const HT = '\t';
static char const WHITE_SPACES[] = {SP, HT, '\0'};
static char const CR = '\r';
static char const LF = '\n';
static char const CRLF[] = {CR, LF, '\0'};

namespace header {
static char const CONTENT_LENGTH[] = "content-Length";
static char const LOWER_CONTENT_LENGTH[] = "content-length";
static char const CONTENT_TYPE[] = "content-Type";
static char const LOWER_CONTENT_TYPE[] = "content-type";
} // namespace header

namespace cgiMeta {
static char const CONTENT_LENGTH[] = "CONTENT_LENGTH";
static char const CONTENT_TYPE[] = "CONTENT_TYPE";
static char const REQUEST_METHOD[] = "REQUEST_METHOD";
static char const QUERY_STRING[] = "QUERY_STRING";
} // namespace cgiMeta

} // namespace http

#endif // CONSTANTS_HPP