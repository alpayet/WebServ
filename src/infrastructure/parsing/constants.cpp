/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 04:30:13 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/06 22:09:34 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/parsing/constants.hpp"

namespace parse {
char const COLON = ':';
char const SP = ' ';
char const HT = '\t';
char const WHITE_SPACES[3] = {SP, HT, '\0'};
char const CR = '\r';
char const LF = '\n';
char const CRLF[3] = {CR, LF, '\0'};

namespace header {
char const CONTENT_LENGTH[] = "Content-Length";
char const LOWER_CONTENT_LENGTH[] = "content-length";
char const CONTENT_TYPE[] = "Content-Type";
char const LOWER_CONTENT_TYPE[] = "content-type";
} // namespace header

std::size_t const DEFAULT_MAX_REQUEST_LINE_SIZE = 8192;
std::size_t const DEFAULT_MAX_HEADER_LINE_SIZE = 8192;
std::size_t const DEFAULT_MAX_HEADER_COUNT = 100;
std::size_t const DEFAULT_MAX_BODY_SIZE = 1048576;

} // namespace parse