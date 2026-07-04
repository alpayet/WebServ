/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorLookup.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 04:01:36 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/04 22:33:45 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPERRORLOOKUP_HPP
#define HTTPERRORLOOKUP_HPP

#include "application/Exception.hpp"
#include "domain/Exception.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"
#include "infrastructure/storage/file_system/Exception.hpp"

namespace http {
unsigned short toStatusCode(Exception::ErrorCode errorCode);
unsigned short toStatusCode(fileSystem::Exception::ErrorCode errorCode);
unsigned short toStatusCode(app::Exception::ErrorCode errorCode);
unsigned short toStatusCode(domain::Exception::ErrorCode errorCode);
} // namespace http

#endif // HTTPERRORLOOKUP_HPP