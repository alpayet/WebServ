/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiResponseMapper.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 21:02:31 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/08 21:58:28 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIRESPONSEMAPPER_HPP
#define CGIRESPONSEMAPPER_HPP

namespace cgi {
class Response;
} // namespace cgi

namespace http {

class Response;

class CgiResponseMapper
{
  public:
	static Response toHttpResponse(cgi::Response const &cgiResponse);

  private:
	CgiResponseMapper(void);
};
} // namespace http

#endif // CGIRESPONSEMAPPER_HPP