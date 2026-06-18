/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Methods.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 19:24:20 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/15 21:31:41 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPMETHODS_HPP
#define HTTPMETHODS_HPP

#include <string>

namespace http {
static char const GET[] = "GET";
static char const POST[] = "POST";
static char const DELETE[] = "DELETE";
static char const HEAD[] = "HEAD";
static char const PUT[] = "PUT";
static char const LINK[] = "LINK";
static char const UNLINK[] = "UNLINK";
static char const HEAD[] = "HEAD";

bool isMethodSupported(std::string const &method);
bool expectsBody(std::string const &method);
} // namespace http

#endif // HTTPMETHODS_HPP