/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 03:46:22 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/05 23:35:52 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgi/constants.hpp"

namespace cgi {
namespace meta {
char const CONTENT_LENGTH[] = "CONTENT_LENGTH";
char const CONTENT_TYPE[] = "CONTENT_TYPE";
char const REQUEST_METHOD[] = "REQUEST_METHOD";
char const QUERY_STRING[] = "QUERY_STRING";
} // namespace meta
} // namespace cgi
