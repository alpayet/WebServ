/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 04:30:13 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/13 17:34:27 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/parsing/constants.hpp"

namespace parse {
char const COLON = ':';
char const SP = ' ';
char const HT = '\t';
char const WHITE_SPACES[3] = {SP, HT, '\0'};
char const CR = '\r';
char const LF = '\n';
char const CRLF[3] = {CR, LF, '\0'};
char const QUERY_DELIMITER = '?';

} // namespace parse