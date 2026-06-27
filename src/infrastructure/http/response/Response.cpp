/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 06:01:36 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/27 06:03:56 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "infrastructure/http/response/Response.hpp"

namespace http {

void Response::reset(void)
{
	headers.clear();
	body.clear();
}
} // namespace http
