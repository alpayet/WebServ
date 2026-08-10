/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiResponse.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 21:02:31 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/09 22:21:26 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIRESPONSEMAPPER_HPP
#define CGIRESPONSEMAPPER_HPP

namespace cgi {
class Response;
} // namespace cgi

namespace http {
class Response;

namespace mapper {
class CgiResponse
{
  public:
	static Response toHttpResponse(cgi::Response const &cgiResponse);

  private:
	CgiResponse(void);
};
} // namespace mapper

} // namespace http

#endif // CGIRESPONSEMAPPER_HPP