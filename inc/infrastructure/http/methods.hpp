/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 19:24:20 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/06 05:03:16 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPMETHODS_HPP
#define HTTPMETHODS_HPP

#include <string>

namespace http {
extern char const GET[];
extern char const POST[];
extern char const DELETE[];
extern char const HEAD[];
extern char const PUT[];
extern char const LINK[];
extern char const UNLINK[];

bool is_method_supported(std::string const &method);
bool expects_body(std::string const &method);
} // namespace http

#endif // HTTPMETHODS_HPP