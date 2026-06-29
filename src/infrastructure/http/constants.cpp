/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 20:20:55 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/30 00:49:43 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/constants.hpp"

namespace http {

char const COLON = ':';
char const SP = ' ';
char const HT = '\t';
char const WHITE_SPACES[3] = {SP, HT, '\0'};
char const CR = '\r';
char const LF = '\n';
char const CRLF[3] = {CR, LF, '\0'};

namespace header {
char const CONTENT_LENGTH[] = "content-Length";
char const LOWER_CONTENT_LENGTH[] = "content-length";
char const CONTENT_TYPE[] = "content-Type";
char const LOWER_CONTENT_TYPE[] = "content-type";
} // namespace header

namespace cgiMeta {
char const CONTENT_LENGTH[] = "CONTENT_LENGTH";
char const CONTENT_TYPE[] = "CONTENT_TYPE";
char const REQUEST_METHOD[] = "REQUEST_METHOD";
char const QUERY_STRING[] = "QUERY_STRING";
} // namespace cgiMeta

} // namespace http