/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 03:45:16 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:26:56 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGICONSTANTS_HPP
#define CGICONSTANTS_HPP

namespace webserv {
namespace cgi {
namespace meta {
extern char const CONTENT_LENGTH[];
extern char const CONTENT_TYPE[];
extern char const REQUEST_METHOD[];
extern char const QUERY_STRING[];
extern char const HTTP_COOKIE[];
} // namespace meta
} // namespace cgi
} // namespace webserv

#endif // CGICONSTANTS_HPP
