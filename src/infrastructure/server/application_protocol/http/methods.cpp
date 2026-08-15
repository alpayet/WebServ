/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 19:24:20 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/15 14:14:41 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/server/application_protocol/http/methods.hpp"
#include <set>

namespace webserv {
namespace http {

char const GET[] = "GET";
char const POST[] = "POST";
char const DELETE[] = "DELETE";
char const HEAD[] = "HEAD";
char const PUT[] = "PUT";
char const LINK[] = "LINK";
char const UNLINK[] = "UNLINK";

bool is_method_supported(std::string const &method)
{
	static char const *supported_methods[] = {
		GET, POST, DELETE, HEAD, PUT, LINK, UNLINK,
	};
	static size_t const methods_nb = sizeof(supported_methods) / sizeof(supported_methods[0]);

	static std::set<std::string> const supported(supported_methods, supported_methods + methods_nb);

	return (supported.find(method) != supported.end());
}

bool expects_body(std::string const &method)
{
	static char const *expects_body_methods[] = {
		POST,
		PUT,
	};
	static size_t const methods_nb = sizeof(expects_body_methods) / sizeof(expects_body_methods[0]);

	static std::set<std::string> const expects_body(
		expects_body_methods, expects_body_methods + methods_nb
	);

	return (expects_body.find(method) != expects_body.end());
}
} // namespace http
}