/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:35:40 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/13 03:12:12 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUESTPARSER_HPP
#define HTTPREQUESTPARSER_HPP

#include "infrastructure/server/application_protocol/http/request/Request.hpp"
#include <map>
#include <string>
#include <vector>

namespace parse {
class IValidationPolicy;
} // namespace parse

namespace http {
class IHttpVersionProvider;

namespace request {
class Parser
{
  public:
	enum Step
	{
		START,
		REQUEST_LINE,
		HEADER,
		BODY,
		COMPLETE
	};

	struct State
	{
		State(void);

		Step		step;
		Request		request;
		std::size_t currenLineSize;
		std::size_t currentHeaderCount;
		std::size_t bodyBytesRead;

		void reset(void);

	  private:
		State(State const &src);
		State &operator=(State const &rhs);
	};

  public:
	Parser(
		parse::IValidationPolicy const &validationPolicy,
		IHttpVersionProvider const	   &httpVersionProvider
	);

	Step parse(std::vector<char> &inputBuf, State &state);

  private:
	Parser(Parser const &src);
	Parser &operator=(Parser const &rhs);

	std::size_t _maxRequestLineSize;
	std::size_t _maxHeaderLineSize;
	std::size_t _maxHeaderCount;
	std::size_t _maxBodySize;

	IHttpVersionProvider const &_httpVersionProvider;

	void parseRequestLine(
		std::vector<char>::const_iterator itStart,
		std::vector<char>::const_iterator itLineEnd,
		Request							 &request
	);
	void parseHeaderLine(
		std::vector<char>::const_iterator itStart,
		std::vector<char>::const_iterator itLineEnd,
		Request							 &request
	);

	void parseContentLength(Request &request);

	void parseBody(std::vector<char> const &inputBuf, Request &request, std::size_t &bodyBytesRead);

	std::string extractMethod(
		std::vector<char>::const_iterator &it, std::vector<char>::const_iterator itLineEnd
	);
	void extractTargetandQuery(
		std::vector<char>::const_iterator &it,
		std::vector<char>::const_iterator  itLineEnd,
		std::string						  &target,
		std::string						  &query
	);
	std::string extractProtocol(
		std::vector<char>::const_iterator &it, std::vector<char>::const_iterator itLineEnd
	);

	void validateRequestLineSize(std::size_t size);
	void validateHeaderLineSize(std::size_t size);
	void validateHeaderCount(std::size_t size);
	void validateBodySize(std::size_t size);
};
} // namespace request

} // namespace http

#endif // HTTPREQUESTPARSER_HPP