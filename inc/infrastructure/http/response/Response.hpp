/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 01:47:49 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/02 00:15:20 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include "application/Exception.hpp"
#include "domain/Exception.hpp"
#include "infrastructure/http/exceptions/Exception.hpp"
#include "infrastructure/storage/file_system/Exception.hpp"
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
	Builder	 &withBody(std::string const &body);
	Builder	 &withBody(char const *body);
	Response &build(void);

	template <typename ExceptionErrorCode> Response &buildError(ExceptionErrorCode const errorCode);

	// Response &buildFixed(unsigned short const statusCode);

  private:
	Response _response;
};
} // namespace http

#include "Response.tpp"

#endif // HTTPRESPONSE_HPP