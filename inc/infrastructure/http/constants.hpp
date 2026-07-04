/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 21:09:41 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/04 03:46:08 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPCONSTANTS_HPP
#define HTTPCONSTANTS_HPP

namespace http {

extern char const COLON;
extern char const SP;
extern char const HT;
extern char const WHITE_SPACES[3];
extern char const CR;
extern char const LF;
extern char const CRLF[3];

namespace header {
extern char const CONTENT_LENGTH[];
extern char const LOWER_CONTENT_LENGTH[];
extern char const CONTENT_TYPE[];
extern char const LOWER_CONTENT_TYPE[];
} // namespace header

} // namespace http

#endif // HTTPCONSTANTS_HPP