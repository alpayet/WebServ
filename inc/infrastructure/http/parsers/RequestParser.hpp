/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:35:40 by alpayet           #+#    #+#             */
/*   Updated: 2026/05/18 19:52:12 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUESTPARSER_HPP
# define HTTPREQUESTPARSER_HPP

# include "ParsingState.hpp"
# include <string>
# include <vector>
# include <map>

namespace Http
{
	class RequestParser
	{
		public:
			static Http::ParsingState::Step parse(
				std::vector<char> const &readBuf, Http::ParsingState &context);

		private:
			RequestParser(void) {}
	};
}

#endif