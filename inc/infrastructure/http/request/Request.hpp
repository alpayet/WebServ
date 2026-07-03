/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:49:02 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/03 20:24:38 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include "BodyFile.hpp"
#include <map>
#include <string>

namespace http {

class Request
{
  public:
	Request(void);

	std::map<std::string, std::string> headers;
	std::string						   method;
	std::string						   target;
	std::string						   protocol;
	std::string						   query;
	std::size_t						   contentLength;
	request::BodyFile				   body;

	void reset(void);

  private:
	Request(Request const &src);
	Request &operator=(Request const &rhs);
};
} // namespace http

#endif // HTTPREQUEST_HPP