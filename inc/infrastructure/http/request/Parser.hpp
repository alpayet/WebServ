/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:35:40 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/27 05:25:49 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUESTPARSER_HPP
#define HTTPREQUESTPARSER_HPP

#include "infrastructure/http/request/Request.hpp"
#include <map>
#include <string>
#include <vector>

namespace http {
class IRequestValidationPolicy;
class IHttpVersionProvider;

namespace request {
class Parser
{
  public:
	enum Step
	{
		start,
		requestLine,
		header,
		body,
		complete
	};

	class State
	{
	  public:
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
		IRequestValidationPolicy &requestValidationPolicy, IHttpVersionProvider &httpVersionProvider
	);

	Step parse(std::vector<char> &inputBuf, State &state);

  private:
	Parser(Parser const &src);
	Parser &operator=(Parser const &rhs);

	std::size_t _maxRequestLineSize;
	std::size_t _maxHeaderLineSize;
	std::size_t _maxHeaderCount;
	std::size_t _maxBodySize;

	IRequestValidationPolicy &_requestValidationPolicy;
	IHttpVersionProvider	 &_httpVersionProvider;

	static std::size_t const DEFAULT_MAX_REQUEST_LINE_SIZE = 8192;
	static std::size_t const DEFAULT_MAX_HEADER_LINE_SIZE = 8192;
	static std::size_t const DEFAULT_MAX_HEADER_COUNT = 100;
	static std::size_t const DEFAULT_MAX_BODY_SIZE = 1048576;

	void parseRequestLine(
		std::vector<char>::const_iterator itStart,
		std::vector<char>::const_iterator itLineEnd,
		State							 &state
	);
	void parseHeaderLine(
		std::vector<char>::const_iterator itStart,
		std::vector<char>::const_iterator itLineEnd,
		State							 &state
	);
	void parseContentLength(State &state);
	void parseBody(std::vector<char> const &inputBuf, State &state);

	std::string extractMethod(
		std::vector<char>::const_iterator &it, std::vector<char>::const_iterator itLineEnd
	);
	void extractTargetandQuery(
		std::vector<char>::const_iterator &it,
		std::vector<char>::const_iterator  itLineEnd,
		State							  &state
	);
	std::string extractProtocol(
		std::vector<char>::const_iterator &it, std::vector<char>::const_iterator itLineEnd
	);

	static bool hasLineBreak(
		std::vector<char>::const_iterator itStart, std::vector<char>::const_iterator itEnd
	);

	static std::vector<char>::iterator findCRLF(std::vector<char> &inputBuf);

	void validateRequestLineSize(std::size_t size);
	void validateHeaderLineSize(std::size_t size);
	void validateHeaderCount(std::size_t size);
};
} // namespace request

} // namespace http

#endif // HTTPREQUESTPARSER_HPP