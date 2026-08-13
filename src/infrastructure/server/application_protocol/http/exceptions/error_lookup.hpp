/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_lookup.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 04:01:36 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/13 17:36:36 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPERRORLOOKUP_HPP
#define HTTPERRORLOOKUP_HPP

#include "application/Exception.hpp"
#include "infrastructure/server/application_protocol/cgi/Exception.hpp"
#include "domain/Exception.hpp"
#include "infrastructure/server/application_protocol/http/exceptions/Exception.hpp"
#include "infrastructure/storage/file_system/Exception.hpp"

namespace http {
unsigned short to_status_code(Exception::ErrorCode error_code);
unsigned short to_status_code(fileSystem::Exception::ErrorCode error_code);
unsigned short to_status_code(cgi::Exception::ErrorCode error_code);
unsigned short to_status_code(app::Exception::ErrorCode error_code);
unsigned short to_status_code(domain::Exception::ErrorCode error_code);
} // namespace http

#endif // HTTPERRORLOOKUP_HPP