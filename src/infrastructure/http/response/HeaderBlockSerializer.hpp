/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderBlockSerializer.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 22:13:21 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/27 05:59:54 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERBLOCKSERIALIZER_HPP
#define HEADERBLOCKSERIALIZER_HPP

#include <string>
#include <vector>

namespace http {

class Response;

namespace response {
class HeaderBlockSerializer
{
  public:
	static void serialize(
		std::vector<char> &outputBuf, Response const &response, std::string const &httpVersion
	);

  private:
	HeaderBlockSerializer(HeaderBlockSerializer const &src);
	HeaderBlockSerializer &operator=(HeaderBlockSerializer const &rhs);
};
} // namespace response
} // namespace http

#endif // HEADERBLOCKSERIALIZER_HPP