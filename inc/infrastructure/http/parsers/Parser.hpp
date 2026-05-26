/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:35:40 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/26 19:19:18 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUESTPARSER_HPP
#define HTTPREQUESTPARSER_HPP

#include "ParsingState.hpp"
#include <map>
#include <string>
#include <vector>

namespace http
{
	class Parser
	{
	  public:
		static ParsingState::Step parse(std::vector<char> &readBuf, ParsingState &state);

	  private:
		Parser(void) {}

		static char const		 _crlf[];
		static std::size_t const _crlfSize;
		static char const		 _whiteSpaces[];
		static std::size_t const _whiteSpacesSize[];

		static void parseRequestLine(
			std::vector<char>::const_iterator itStart,
			std::vector<char>::const_iterator itLineEnd,
			ParsingState					 &state
		);
		static void parseHeaderLine(
			std::vector<char>::const_iterator itStart,
			std::vector<char>::const_iterator itLineEnd,
			ParsingState					 &state
		);
		static void parseContentLength(ParsingState &state);
		static void parseBody(
			std::vector<char>::const_iterator itStart,
			std::vector<char>::const_iterator itLineEnd,
			ParsingState					 &state
		);

		static std::string Parser::extractMethod(
			std::vector<char>::const_iterator &it, std::vector<char>::const_iterator itLineEnd
		);
		static std::string Parser::extractTarget(
			std::vector<char>::const_iterator &it, std::vector<char>::const_iterator itLineEnd
		);
		static std::string Parser::extractProtocol(
			std::vector<char>::const_iterator &it, std::vector<char>::const_iterator itLineEnd
		);

		static bool hasLineBreak(
			std::vector<char>::const_iterator itStart, std::vector<char>::const_iterator itEnd
		);

		static std::vector<char>::iterator findCRLF(std::vector<char> &readBuf);
	};
} // namespace http

#endif // HTTPREQUESTPARSER_HPP