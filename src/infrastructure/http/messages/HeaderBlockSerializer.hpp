/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderBlockSerializer.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 22:16:37 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/18 22:46:45 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/Constants.hpp"
#include "infrastructure/http/messages/HeaderBlockSerializer.hpp"
#include "infrastructure/http/messages/Response.hpp"
#include <sstream>

namespace http {
std::vector<char> HeaderBlockSerializer::serialize(Response const &response)
{
	std::stringstream HeaderBlock;

	HeaderBlock << response.protocol << SP << response.status.statusCode << SP
				<< response.status.reason << CRLF;
}
} // namespace http
