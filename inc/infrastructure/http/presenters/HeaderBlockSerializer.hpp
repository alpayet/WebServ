/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderBlockSerializer.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 22:13:21 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/18 22:16:01 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERBLOCKSERIALIZER_HPP
#define HEADERBLOCKSERIALIZER_HPP

#include <vector>

namespace http {
struct Response;

class HeaderBlockSerializer
{
  public:
	static std::vector<char> serialize(Response const &response);

  private:
	HeaderBlockSerializer(HeaderBlockSerializer const &src);
	HeaderBlockSerializer &operator=(HeaderBlockSerializer const &rhs);
};
} // namespace http

#endif // HEADERBLOCKSERIALIZER_HPP