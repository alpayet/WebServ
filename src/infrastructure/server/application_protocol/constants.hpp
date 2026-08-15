/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 17:41:32 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 13:22:55 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#define SERVEUR_SOFTWARE "webserv/1.0"

namespace webserv {
namespace headers {
extern char const CONTENT_LENGTH[];
extern char const CONTENT_TYPE[];
extern char const CONNECTION[];
extern char const COOKIE[];
extern char const SET_COOKIE[];
extern char const STATUS[];
extern char const LOCATION[];
} // namespace headers
}

#endif // CONSTANTS_HPP