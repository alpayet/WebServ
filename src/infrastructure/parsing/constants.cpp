/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 04:30:13 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/08 03:15:58 by alpayet          ###   ########.fr       */
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

char const CONTENT_LENGTH[] = "content-length";
char const CONTENT_TYPE[] = "content-type";
char const STATUS[] = "status";
char const LOCATION[] = "location";

std::size_t const DEFAULT_MAX_REQUEST_LINE_SIZE = 8192;
std::size_t const DEFAULT_MAX_HEADER_LINE_SIZE = 8192;
std::size_t const DEFAULT_MAX_HEADER_COUNT = 100;
std::size_t const DEFAULT_MAX_BODY_SIZE = 1048576;

} // namespace parse