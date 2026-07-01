/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorLookup.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 04:01:36 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/01 04:22:53 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPERRORLOOKUP_HPP
#define HTTPERRORLOOKUP_HPP

#include "application/Exception.hpp"
#include "domain/Exception.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"
#include "infrastructure/storage/file_system/Exception.hpp"

namespace http {
unsigned short toHttpStatusCode(Exception::ErrorCode const errorCode);
unsigned short toHttpStatusCode(app::Exception::ErrorCode const errorCode);
unsigned short toHttpStatusCode(domain::Exception::ErrorCode const errorCode);
unsigned short toHttpStatusCode(fileSystem::Exception::ErrorCode const errorCode);
} // namespace http

#endif // HTTPERRORLOOKUP_HPP