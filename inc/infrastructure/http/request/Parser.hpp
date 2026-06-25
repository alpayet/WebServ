/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:35:40 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/25 20:00:51 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUESTPARSER_HPP
#define HTTPREQUESTPARSER_HPP

#include "infrastructure/http/Context.hpp"
#include "infrastructure/http/request/Request.hpp"
#include <map>
#include <string>
#include <vector>

namespace http {
class IRequestValidationPolicy;
class IVersionProvider;

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

	struct State
	{
		State(void) : step(start), currenLineSize(0), currentHeaderCount(0), bodyBytesRead(0) {}

		Step		step;
		Request		request;
		std::size_t currenLineSize;
		std::size_t currentHeaderCount;
		std::size_t bodyBytesRead;
	};

  public:
	Parser(IRequestValidationPolicy &requestValidationPolicy, IVersionProvider &versionProvider);

	Step parse(Context::Input &context);

  private:
	Parser(Parser const &src);
	Parser &operator=(Parser const &rhs);

	IRequestValidationPolicy &_requestValidationPolicy;
	IVersionProvider		 &_versionProvider;

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

	std::string Parser::extractMethod(
		std::vector<char>::const_iterator &it, std::vector<char>::const_iterator itLineEnd
	);
	void Parser::extractTargetandQuery(
		std::vector<char>::const_iterator &it,
		std::vector<char>::const_iterator  itLineEnd,
		State							  &state
	);
	std::string Parser::extractProtocol(
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