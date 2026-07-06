/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 02:28:27 by alpayet           #+#    #+#             */
/*   Updated: 2026/07/06 23:58:55 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIPARSER_HPP
#define CGIPARSER_HPP

#include "cgi/Response.hpp"
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
		header,
		body,
		complete
	};

	class State
	{
	  public:
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
	Parser(parse::IValidationPolicy &validationPolicy);

	Step parse(std::vector<char> &inputBuf, State &state);

  private:
	Parser(Parser const &src);
	Parser &operator=(Parser const &rhs);

	std::size_t _maxRequestLineSize;
	std::size_t _maxHeaderLineSize;
	std::size_t _maxHeaderCount;
	std::size_t _maxBodySize;

	parse::IValidationPolicy &_validationPolicy;

	void classifyResponse(Response &response, Step &step);

	void parseHeaderLine(
		std::vector<char>::const_iterator	itStart,
		std::vector<char>::const_iterator	itLineEnd,
		std::map<std::string, std::string> &headers
	);
	void parseContentLength(Response &response);
	void
	parseBody(std::vector<char> const &inputBuf, Response &response, std::size_t &bodyBytesRead);

	void validateHeaderLineSize(std::size_t size);
	void validateHeaderCount(std::size_t size);
	void validateBodySize(std::size_t size);
};
} // namespace cgi

#endif // CGIPARSER_HPP