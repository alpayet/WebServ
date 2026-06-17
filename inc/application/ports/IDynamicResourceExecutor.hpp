/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IDynamicResourceExecutor.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 21:49:57 by alpayet           #+#    #+#             */
/*   Updated: 2026/06/17 09:54:23 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IDYNAMICRESOURCEEXECUTOR_HPP
#define IDYNAMICRESOURCEEXECUTOR_HPP

#include <map>
#include <string>

namespace app {
class IDynamicResourceExecutor
{
  public:
	virtual ~IDynamicResourceExecutor(void) {}

	virtual void execute(
		std::string const						 &resourcePath,
		std::string const						 &bodyPath,
		std::map<std::string, std::string> const &metaVariables
	) = 0;
};
} // namespace app

#endif // IDYNAMICRESOURCEEXECUTOR_HPP