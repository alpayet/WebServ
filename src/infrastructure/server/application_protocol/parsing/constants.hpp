/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 04:29:24 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:21:26 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSINGCONSTANTS_HPP
#define PARSINGCONSTANTS_HPP

#include <cstdlib>

namespace webserv {
namespace parse {
extern char const COLON;
extern char const SP;
extern char const HT;
extern char const WHITE_SPACES[3];
extern char const CR;
extern char const LF;
extern char const CRLF[3];
extern char const QUERY_DELIMITER;

} // namespace parse
}

#endif // PARSINGCONSTANTS_HPP
