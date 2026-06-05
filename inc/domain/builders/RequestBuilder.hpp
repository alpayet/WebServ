/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestBuilder.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 01:41:40 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/30 01:55:42 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTBUILDER_HPP
#define REQUESTBUILDER_HPP

#include "domain/entities/RequestEntity.hpp"
#include <map>
#include <string>

class RequestBuilder
{
  public:
	RequestBuilder(void) {}

	RequestBuilder &withTarget(std::string const &target);
	RequestBuilder &withProtocol(std::string const &protocol);
	RequestBuilder &withHeaders(std::map<std::string, std::string> const &headers);

	RequestEntity build(void);

  private:
	RequestBuilder(RequestBuilder const &src);
	RequestBuilder &operator=(RequestBuilder const &rhs);

	std::string						   _target;
	std::string						   _protocol;
	std::map<std::string, std::string> _headers;
};

#endif