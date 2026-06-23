/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 01:47:49 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/23 04:00:25 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include <string>
#include <vector>

namespace http {
namespace response {

struct Response
{
  public:
	class Builder;

	struct Status
	{
		unsigned short statusCode;
		std::string	   reason;
	};
	struct Header
	{
		std::string key;
		std::string value;
	};

	std::string			protocol;
	Status				status;
	std::vector<Header> headers;
	std::vector<char>	body;
};

class Response::Builder
{
  public:
	Builder		   &withProtocol(std::string const &protocol);
	Builder		   &withStatus(Response::Status const &status);
	Builder		   &withHeader(std::string const &key, std::string const &value);
	Builder		   &withBody(std::vector<char> const &body);
	Response const &build(void) const;

  private:
	Response _response;
};
} // namespace response
} // namespace http

#endif // HTTPRESPONSE_HPP