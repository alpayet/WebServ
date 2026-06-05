/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Methods.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 19:24:20 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/26 18:01:07 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/Methods.hpp"
#include <set>

namespace http
{
	bool isMethodSupported(std::string const &method)
	{
		static const char *supported_methods[] = {
			"GET", "POST", "DELETE", "HEAD", "PUT", "LINK", "UNLINK",
		};
		static const size_t methods_nb = sizeof(supported_methods) / sizeof(supported_methods[0]);

		static const std::set<std::string> supported(
			supported_methods, supported_methods + methods_nb
		);

		return (supported.find(method) != supported.end());
	}

	bool expectsBody(std::string const &method)
	{
		static const char *expects_body_methods[] = {
			"POST",
			"PUT",
		};
		static const size_t methods_nb =
			sizeof(expects_body_methods) / sizeof(expects_body_methods[0]);

		static const std::set<std::string> expects_body(
			expects_body_methods, expects_body_methods + methods_nb
		);

		return (expects_body.find(method) != expects_body.end());
	}
} // namespace http