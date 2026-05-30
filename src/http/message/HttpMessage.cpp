/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpMessage.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 22:57:54 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/30 01:41:16 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpMessage.hpp"

HttpMessage::HttpMessage(void) : _headers() {}

HttpMessage::HttpMessage(std::map<std::string, std::string> const &headers) : _headers(headers) {}

HttpMessage::HttpMessage(const HttpMessage &src) : _headers(src._headers) {}

HttpMessage &HttpMessage::operator=(HttpMessage const &rhs)
{
	if (this != &rhs)
		_headers = rhs._headers;
	return (*this);
}