/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 01:47:49 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/27 06:00:38 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include <string>
#include <vector>

namespace http {
class Response
{
  public:
	class Builder;
	struct Header
	{
		std::string key;
		std::string value;
	};

  public:
	unsigned short		statusCode;
	std::vector<Header> headers;
	std::vector<char>	body;

	void reset(void);
};

class Response::Builder
{
  public:
	Builder	 &withStatusCode(unsigned short const statusCode);
	Builder	 &withHeader(std::string const &key, std::string const &value);
	Builder	 &withBody(std::vector<char> const &body);
	Response &build(void);

  private:
	Response _response;
};

} // namespace http

#endif // HTTPRESPONSE_HPP