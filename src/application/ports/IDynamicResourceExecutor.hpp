/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IDynamicResourceExecutor.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpayet <alpayet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 21:49:57 by alpayet           #+#    #+#             */
/*   Updated: 2026/08/09 21:25:26 by alpayet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IDYNAMICRESOURCEEXECUTOR_HPP
#define IDYNAMICRESOURCEEXECUTOR_HPP

#include <map>
#include <string>

namespace app {
class IResourceReader;

class IDynamicResourceExecutor
{
  public:
	virtual ~IDynamicResourceExecutor(void) {}

	virtual int execute(
		std::string const						 &resourcePath,
		std::string const						 &bodyPath,
		std::map<std::string, std::string> const &metaVariables
	) = 0;
};
} // namespace app

#endif // IDYNAMICRESOURCEEXECUTOR_HPP