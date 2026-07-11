/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 04:29:24 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/11 20:23:34 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSINGCONSTANTS_HPP
#define PARSINGCONSTANTS_HPP

#include <cstdlib>

namespace parse {
extern char const COLON;
extern char const SP;
extern char const HT;
extern char const WHITE_SPACES[3];
extern char const CR;
extern char const LF;
extern char const CRLF[3];
extern char const QUERY_DELIMITER;

extern std::size_t const DEFAULT_MAX_REQUEST_LINE_SIZE;
extern std::size_t const DEFAULT_MAX_HEADER_LINE_SIZE;
extern std::size_t const DEFAULT_MAX_HEADER_COUNT;
extern std::size_t const DEFAULT_MAX_BODY_SIZE;

} // namespace parse

#endif // PARSINGCONSTANTS_HPP
