/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 02:28:27 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/13 17:36:36 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIPARSER_HPP
#define CGIPARSER_HPP

#include "infrastructure/server/application_protocol/cgi/Response.hpp"
#include <vector>

namespace parse {
class IValidationPolicy;
} // namespace parse

namespace cgi {

class Parser
{
  public:
	enum Step
	{
		HEADER,
		BODY,
		COMPLETE
	};

	struct State
	{
		State(void);

		Step		step;
		Response	response;
		std::size_t currenLineSize;
		std::size_t currentHeaderCount;
		std::size_t bodyBytesRead;

		void reset(void);

	  private:
		State(State const &src);
		State &operator=(State const &rhs);
	};

  public:
	Parser(parse::IValidationPolicy const &validationPolicy);

	Step parse(std::vector<char> &inputBuf, bool isCgiEof, State &state);

  private:
	Parser(Parser const &src);
	Parser &operator=(Parser const &rhs);

	std::size_t _maxRequestLineSize;
	std::size_t _maxHeaderLineSize;
	std::size_t _maxHeaderCount;
	std::size_t _maxBodySize;

	void classifyResponse(Response &response);

	void parseHeaderLine(
		std::vector<char>::const_iterator itStart,
		std::vector<char>::const_iterator itLineEnd,
		Response						 &response
	);
	void parseStatus(Response &response);
	void parseLocation(Response &response);
	void parseContentLength(Response &response);
	void
	parseBody(std::vector<char> const &inputBuf, Response &response, std::size_t &bodyBytesRead);

	void validateHeaderLineSize(std::size_t size);
	void validateHeaderCount(std::size_t size);
	void validateBodySize(std::size_t size);
};
} // namespace cgi

#endif // CGIPARSER_HPP