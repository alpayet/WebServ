/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:35:40 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/18 22:28:03 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUESTPARSER_HPP
#define HTTPREQUESTPARSER_HPP

#include "ParsingState.hpp"
#include <map>
#include <string>
#include <vector>

namespace http {
class IRequestValidationPolicy;
class IVersionProvider;

class Parser
{
  public:
	Parser(IRequestValidationPolicy &requestValidationPolicy, IVersionProvider &versionProvider);

	ParsingState::Step parse(std::vector<char> &readBuf, ParsingState &state);

  private:
	Parser(Parser const &src);
	Parser &operator=(Parser const &rhs);

	IRequestValidationPolicy &_requestValidationPolicy;
	IVersionProvider		 &_versionProvider;

	void parseRequestLine(
		std::vector<char>::const_iterator itStart,
		std::vector<char>::const_iterator itLineEnd,
		ParsingState					 &state
	);
	void parseHeaderLine(
		std::vector<char>::const_iterator itStart,
		std::vector<char>::const_iterator itLineEnd,
		ParsingState					 &state
	);
	void parseContentLength(ParsingState &state);
	void parseBody(std::vector<char> const &readBuf, ParsingState &state);

	std::string Parser::extractMethod(
		std::vector<char>::const_iterator &it, std::vector<char>::const_iterator itLineEnd
	);
	void Parser::extractTargetandQuery(
		std::vector<char>::const_iterator &it,
		std::vector<char>::const_iterator  itLineEnd,
		ParsingState					  &state
	);
	std::string Parser::extractProtocol(
		std::vector<char>::const_iterator &it, std::vector<char>::const_iterator itLineEnd
	);

	static bool hasLineBreak(
		std::vector<char>::const_iterator itStart, std::vector<char>::const_iterator itEnd
	);

	static std::vector<char>::iterator findCRLF(std::vector<char> &readBuf);

	void validateRequestLineSize(std::size_t size);
	void validateHeaderLineSize(std::size_t size);
	void validateHeaderCount(std::size_t size);
};
} // namespace http

#endif // HTTPREQUESTPARSER_HPP